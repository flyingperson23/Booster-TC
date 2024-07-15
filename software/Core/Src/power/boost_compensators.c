/*
 * boost_compensators.c
 *
 *  Created on: Jul 8, 2024
 *      Author: flyin
 */

#include "power/boost_compensators.h"

Filter2p2z CompensatorV;
Filter2p2z CompensatorI;
Filter2p2z FilterVFF;

float VInv_rms = 1;
float VInvSq_rms = 1;
float I_rq = 0;
float dtc = 0;

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

	Reset2p2zFilter(&CompensatorV);
	Reset2p2zFilter(&CompensatorI);
	Reset2p2zFilter(&FilterVFF);
}

// must pass abs(vac)
void BoostSlowLoop(float vbus, float vac) {
	Run2p2zFilter(&CompensatorV, vref - vbus);
	Run2p2zFilter(&FilterVFF, vac);

	if (FilterVFF.y[0] == 0) {
		VInvSq_rms = 1;
		VInv_rms = 1;
	} else {
		VInv_rms = 1 / (1.1 * FilterVFF.y[0]);
		VInvSq_rms = VInv_rms * VInv_rms;
	}
}

void BoostFastLoop(float vac, float I_L) {
	I_rq = vac * CompensatorV.y[0] * VInvSq_rms;
	fconstrain(&I_rq, 0, vac * GetValue(MAX_AC_I) * VInv_rms);
	dtc = Run2p2zFilter(&CompensatorI, I_L - I_rq);
	fconstrain(&dtc, 0, 0.8);
	// set dtc
}
