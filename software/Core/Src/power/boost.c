/*
 * boost.c
 *
 *  Created on: Jul 8, 2024
 *      Author: flyin
 */

#include <power/boost.h>

Filter2p2z CompensatorV;
Filter2p2z CompensatorI;
Filter2p2z FilterVFF;
Filter2p2z FilterIRMS; // make sure this works



uint8_t enabled = 0;

uint32_t vref = 0;
float VInv_rms = 1;
float VInvSq_rms = 1;
float I_rq = 0;
float dtc = 0;
float vbus = 0;
float I_L = 0;
float vac = 0;
float vac_rms = 0;

uint32_t vbusint = 0;
uint32_t I_Lint = 0;
uint32_t vacint = 0;

uint32_t v_conversion_factor = 200;
float I_conversion_factor = 0.04f; // V/A

float Run2p2zFilter(Filter2p2z * filter, float error) {
	filter->x[2] = filter->x[1];
	filter->x[1] = filter->x[0];
	filter->x[0] = error;

	filter->y[2] = filter->y[1];
	filter->y[1] = filter->y[0];
	filter->y[0] = filter->A1 * filter->y[1] + filter->A2 * filter->y[2] + filter->B0 * filter->x[0] + filter->B1 * filter->x[1] + filter->B2 * filter->x[2];

	return filter->y[0];
}

void Init2p2zFilter(Filter2p2z * filter, float A1, float A2, float B0, float B1, float B2) {
	filter->A1 = A1;
	filter->A2 = A2;
	filter->B0 = B0;
	filter->B1 = B1;
	filter->B2 = B2;
}

void Reset2p2zFilter(Filter2p2z * filter) {
	filter->y[0] = 0;
	filter->y[1] = 0;
	filter->y[2] = 0;
	filter->x[0] = 0;
	filter->x[1] = 0;
	filter->x[2] = 0;
}

void BoostInit() {
	Init2p2zFilter(&CompensatorV, A1_V, A2_V, B0_V, B1_V, B2_V);
	Init2p2zFilter(&CompensatorI, A1_I, A2_I, B0_I, B1_I, B2_I);
	Init2p2zFilter(&FilterVFF, A1_VFF, A2_VFF, B0_VFF, B1_VFF, B2_VFF);
	Init2p2zFilter(&FilterIRMS, A1_VFF, A2_VFF, B0_VFF, B1_VFF, B2_VFF);

	Reset2p2zFilter(&CompensatorV);
	Reset2p2zFilter(&CompensatorI);
	Reset2p2zFilter(&FilterVFF);
	Reset2p2zFilter(&FilterIRMS);

	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, &vacint, 1);

	HAL_ADCEx_Calibration_Start(&hadc4, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc4, &I_Lint, 1);

	HAL_ADCEx_Calibration_Start(&hadc5, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc5, &vbusint, 1);

	HAL_DMA_RegisterCallback(&hdma_adc2, HAL_DMA_XFER_CPLT_CB_ID, &DMATransferComplete_adc2);

	HAL_DMA_RegisterCallback(&hdma_adc4, HAL_DMA_XFER_CPLT_CB_ID, &DMATransferComplete_adc4);

	HAL_DMA_RegisterCallback(&hdma_adc5, HAL_DMA_XFER_CPLT_CB_ID, &DMATransferComplete_adc5);

	HRTIM1->sMasterRegs.MCR |= HRTIM_MCR_TACEN; // Start Timer A
	HRTIM1->sMasterRegs.MCR |= HRTIM_MCR_TDCEN; // start timer D
}

uint8_t flag = 0;

void DMATransferComplete_adc2(DMA_HandleTypeDef *hdma) {
	if (hdma == &hdma_adc2) {
		vac = fabs((vacint << 1) - vrefint_adc) * 3.3f * v_conversion_factor / 4096.0f;
	}
}

void DMATransferComplete_adc4(DMA_HandleTypeDef *hdma) {
	if (hdma == &hdma_adc4) {
		I_L = ((float) I_Lint) * 3.3f * I_conversion_factor / 4096.0f;
		BoostFastLoop();
	}
}

void DMATransferComplete_adc5(DMA_HandleTypeDef *hdma) {
	if (hdma == &hdma_adc5) {
		vbus = ((float) vbusint) * 3.3f * v_conversion_factor / 4096.0f ;
		BoostSlowLoop();
	}
}

void BoostSlowLoop() {
	if (vbus > GetValue(MAX_OUT_V)) {
		fault |= FAULT_OV;
		FaultHandle();
	}
	if (I_L > GetValue(MAX_I_L)) {
		fault |= FAULT_OC;
		FaultHandle();
	}

	Run2p2zFilter(&CompensatorV, vref - vbus);
	Run2p2zFilter(&FilterVFF, vac);
	Run2p2zFilter(&FilterIRMS, I_L);

	if (FilterVFF.y[0] == 0) {
		VInvSq_rms = 1;
		VInv_rms = 1;
		vac_rms = 0;
	} else {
		vac_rms = 1.1 * FilterVFF.y[0];
		VInv_rms = 1 / vac_rms;
		VInvSq_rms = VInv_rms * VInv_rms;
	}

}

void BoostFastLoop() {
	if (enabled) {
		I_rq = vac * CompensatorV.y[0] * VInvSq_rms;
		fconstrain(&I_rq, 0, vac * GetValue(MAX_AC_I) * VInv_rms);
		dtc = Run2p2zFilter(&CompensatorI, I_L - I_rq);
		fconstrain(&dtc, 0, 0.8);
		float compare =  ((float) HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_D].PERxR) * dtc;

		HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP1xR = (uint32_t) compare;
		HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP3xR = ((uint32_t) compare) >> 1;

	} else {
		HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP1xR = 0;
		HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP3xR = 0;
	}


}

void BoostDisable() {
	// stop fast timer?
	HRTIM1->sCommonRegs.ODISR |= HRTIM_OENR_TA2OEN; /* Disable TA2 output */
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP3xR = 0;
	HRTIM1->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP1xR = 0;
	enabled = 0;
}

void BoostEnable() {
	// start fast timer?
	HRTIM1->sCommonRegs.OENR |= HRTIM_OENR_TA2OEN; /* Enable TA2 output */
	enabled = 1;
}
