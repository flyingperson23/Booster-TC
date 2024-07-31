/*
 * booster_tc.c
 *
 *  Created on: Jul 9, 2024
 *      Author: flyin
 */

#include "booster_tc.h"

uint8_t power_state = STATE_OFF;
uint8_t mode = MODE_AUTO;

uint32_t temp_buffer[3] = {0, 0, 0};
float temps[3] = {0.0f, 0.0f, 0.0f};

void stop() {
	SCRBlock();
	PWMStop();
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

	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, temp_buffer, 3);

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

float a = 1;
float b = 1;
float c = 1; //// need to get these for therm!!!!!!!!!!!!!


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

}

void TIM6_DAC_IRQHandler(void) {
	if ((TIM6->SR & TIM_FLAG_UPDATE) == TIM_FLAG_UPDATE) {
		TIM6->SR = ~TIM_FLAG_UPDATE;
		for (int i = 0; i < 2; i++) {
			if (temp_buffer[i] != 0) {
				float R = 10000*CountsToVolts(temps[i]) / (2.9f - CountsToVolts(temps[i]));
				temps[i] = 1.0f / (a + b * log(R) + c * log(R) * log(R) * log(R)) - 273.15f;
			}
		}
		// third temp
		background_loop();
	}
}

uint32_t scr_counter = 0;
void background_loop() {

	// get 24v sense from adc3

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

		if (vbus < 50) {
			LEDSetBlinking(LED_VBUS, 1);
		} else {
			LEDSetBlinking(LED_VBUS, 0);
			float vbusled = 255.0f * vbus / ((float) GetValue(MAX_OUT_V));
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

		// get rms current draw

		if (temps[0] > GetValue(MAX_TEMP) || temps[1] > GetValue(MAX_TEMP)) {
			fault |= FAULT_TEMP;
			FaultHandle();
		}
		if (mode == MODE_AUTO) {
			vref = 400;
			if (power_state == STATE_OFF) {
				power_state = STATE_SCR;
				SCRBlock();
				// disable boost timer
			}
			if (power_state == STATE_SCR) {

				//disable boost timer
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
			}
		} else if (mode == MODE_MANUAL) {

		}
	} else {
		FaultHandle();
	}


}
