/*
 * booster_tc.c
 *
 *  Created on: Jul 9, 2024
 *      Author: flyin
 */

#include "booster_tc.h"

uint8_t power_state = STATE_OFF;
uint8_t mode = MODE_AUTO;

uint32_t temp_buffer[4] = {0, 0, 0, 0};
float temps[3] = {0.0f, 0.0f, 0.0f};
float V24_sense = 24.0f;
uint32_t vrefint_adc = 3600;

StructAvg VAC_avg;
StructAvg IAC_avg;
StructAvg VBUS_avg;

void stop() {
	SCRBlock();
	PWMStop();
	BoostDisable();
	// fill this in
}

void booster_init() {
	SPIInit();
	AddVars();
	FillVars();
	CmdsInit();
	UartInit();
	BoostInit();
	SCRInit();
	PWMInit();

	InitAvg(&VAC_avg);
	InitAvg(&IAC_avg);
	InitAvg(&VBUS_avg);

	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, temp_buffer, 4);
	HAL_DMA_RegisterCallback(&hdma_adc1, HAL_DMA_XFER_CPLT_CB_ID, &DMATransferComplete_adc1);

	HAL_DAC_Start(&hdac2, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac3, DAC_CHANNEL_1);

	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	HAL_COMP_Start(&hcomp6);
	HAL_COMP_Start(&hcomp7);
}

void booster_loop() {

}

double beta[2] = {3950, 3950};

void DMATransferComplete_adc1(DMA_HandleTypeDef *_hdma) {
	if (_hdma == &hdma_adc1) {
		vrefint_adc = temps[3];
		for (int i = 0; i < 2; i++) {
			if (temp_buffer[i] != 0) {
				double a = ((double) temp_buffer[i]) / (vrefint_adc - ((double)temp_buffer[i]));
				if (a != 0) {
					double b = (log(a) / beta[i]) + (1.0 / 298.15);
					double c = (1.0 / b) - 273.15;
					temps[i] = (float) c;
				}
			}
		}
		// third temp - V = T_0 + T_C * T
		// T = (V - T_0) / T_C
		// T_0 = 500mV, T_C = 10 mV/C
		float V = temp_buffer[2] * 3.3f / 4096.0;
		temps[2] = (V - 0.5f) / 0.01f;
		background_loop();
	}
}

uint32_t scr_counter = 0;
void background_loop() {

	AvgInput(&VAC_avg, vac_rms);
	AvgInput(&IAC_avg, FilterIRMS.y[0]);
	AvgInput(&VBUS_avg, vbus);

	AvgCalculate(&IAC_avg);
	AvgCalculate(&VBUS_avg);

	if (temps[0] > GetValue(MAX_TEMP) || temps[1] > GetValue(MAX_TEMP) || temps[2] > GetValue(MAX_TEMP)) {
		fault |= FAULT_TEMP;
		FaultHandle();
	}

    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
    V24_sense = HAL_ADC_GetValue(&hadc3) * 3.3f / 4096.0f;

    if (V24_sense < GetValue(UVLO)) {
    	fault |= FAULT_UVLO;
    	FaultHandle();
    }

	HAL_GPIO_EXTI_Callback(INT_Pin); // make sure we have the right int signal

	HAL_GPIO_WritePin(DRIVE_EN_GPIO_Port, DRIVE_EN_Pin, SET);
	HAL_GPIO_WritePin(PMP_EN_GPIO_Port, PMP_EN_Pin, SET);

	float vdrive = GetValue(VDRIVE) - 10;
	vdrive = (vdrive * 255.0f) / 12.0f;
	fconstrain(&vdrive, 0.0f, 255.0f);
	DriveSet((uint8_t) vdrive);


	float highest_temp = temps[0];
	if (temps[1] > highest_temp) highest_temp = temps[1];
	if (temps[2] > highest_temp) highest_temp = temps[2];

	int ramp_start = GetValue(RAMP_START);
	int ramp_end = GetValue(RAMP_END);

	if (highest_temp < ramp_start) {
		HAL_GPIO_WritePin(FAN_EN_GPIO_Port, FAN_EN_Pin, RESET);
	} else {
		HAL_GPIO_WritePin(FAN_EN_GPIO_Port, FAN_EN_Pin, SET);
		float fan = 255.0f * ((float) (highest_temp - ramp_start)) / ((float) ramp_end - ramp_start);
		fconstrain(&fan, 0.0f, 255.0f);
		FanSet((uint8_t) fan);
	}

	// ocd dac volts = ocd current (A) * ct ratio (mV/A) * 1V/1000mV
	// ocd dac volts = 3.3/4095 * counts -> counts = 4095/3.3 * volts
	// ocd dac counts = ocd current (A) * ct ratio (mV/A) * 1V/1000mV * 4096counts/3.3V
	// ocd:
	uint32_t dac_counts = (uint32_t) ((float) (GetValue(MAX_PRI_I) * GetValue(CT_FACTOR)) * 4095.0f / 3.3f / 1000.0f);
	HAL_DAC_SetValue(&hdac3, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_counts);

	// I_L:
	// counts = max I (A) * 0.04V / 1A * 4096 counts / 3.3V
	dac_counts = (uint32_t) ((float) (GetValue(MAX_I_L)) * 0.04f * 4095.0f / 3.3f);
	HAL_DAC_SetValue(&hdac2, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_counts);

	mode = GPIORead(MODE_IN_GPIO_Port, MODE_IN_Pin);

	if (fault == NOFAULT) {

		if (VBUS_avg.out < 50) {
			LEDSetBlinking(LED_VBUS, 1);
		} else {
			LEDSetBlinking(LED_VBUS, 0);
			float vbusled = 255.0f * VBUS_avg.out / ((float) GetValue(MAX_OUT_V));
			fconstrain(&vbusled, 0.0f, 255.0f);
			LEDSetValue(LED_VBUS, (uint8_t) vbusled);
		}

		if (highest_temp + 10.0f > GetValue(MAX_TEMP)) {
			LEDSetBlinking(LED_TEMP, 1);
		} else {
			LEDSetBlinking(LED_TEMP, 0);
			float templed = 255.0f * (highest_temp - 20.0f) / (GetValue(MAX_TEMP) - 10.0f - 20.0f);
			fconstrain(&templed, 0.0f, 255.0f);
			LEDSetValue(LED_TEMP, (uint8_t) templed);
		}

		if (IAC_avg.out > 0.9f * GetValue(MAX_AC_I)) {
			LEDSetBlinking(LED_I_IN, 1);
		} else {
			LEDSetBlinking(LED_I_IN, 0);
			float iled = 255.0f * IAC_avg.out / (0.9 * GetValue(MAX_AC_I));
			fconstrain(&iled, 0.0f, 255.0f);
			LEDSetValue(LED_I_IN, (uint8_t) iled);
		}

		if (mode == MODE_AUTO) {
			vref = 400;
			if (power_state == STATE_OFF) {
				power_state = STATE_SCR;
				SCRBlock();
				BoostDisable();
			}
			if (power_state == STATE_SCR) {

				BoostDisable();
				scr_counter = (scr_counter + 1) % 100;
				if (scr_counter == 0) {
					SCRIncrement();
				}
				if (SCRBypassStatus()) {
					SCRBypass();
					power_state = STATE_BOOST;
				}
			}
			if (power_state == STATE_BOOST) {
				SCRBypass();
				BoostEnable();
			}
		} else if (mode == MODE_MANUAL) {

		}
	} else {
		FaultHandle();
	}


}
