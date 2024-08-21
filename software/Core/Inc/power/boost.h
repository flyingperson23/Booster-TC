/*
 * boost.h
 *
 *  Created on: Jul 8, 2024
 *      Author: flyin
 */

#ifndef INC_BOOST_H_
#define INC_BOOST_H_

// controls boost converter for bus voltage

#include "sys/vars.h"
#include "sys/util.h"
#include "status/fault.h"
#include "booster_tc.h"

// 2p2z => y[n] = A1 y[n-1] + A2 y[n-2] + B0 x[n] + B1 x[n-1] + B2 x[n-2]

// voltage loop, executes at 6kHz, Fx 7 Hz, volts
#define B0_V (+1.1168785742308580)
#define B1_V (+0.0021915872506436)
#define B2_V (-1.1146869869802145)
#define A1_V (+1.9730118016793023)
#define A2_V (-0.9730118016793024)

// current loop, exectues at 60kHz, Fx 5kHz, input amps
#define B0_I (+0.0088500995985868)
#define B1_I (+0.0002030180598572)
#define B2_I (-0.0086470815387296)
#define A1_I (+0.7779690592966855)
#define A2_I (+0.2220309407033146)

// voltage feedfoward filter
#define B0_VFF (+0.0000876353428621)
#define B1_VFF (+0.0001752706857241)
#define B2_VFF (+0.0000876353428621)
#define A1_VFF (+1.9810149591682376)
#define A2_VFF (-0.9813655005396860)


typedef struct {
	float B0;
	float B1;
	float B2;
	float A1;
	float A2;

	float y[3]; // output
	float x[3]; // input
} Filter2p2z;

float Run2p2zFilter(Filter2p2z * filter, float error);
void Init2p2zFilter(Filter2p2z * filter, float A1, float A2, float B0, float B1, float B2);
void Reset2p2zFilter(Filter2p2z * filter);

extern Filter2p2z CompensatorV;
extern Filter2p2z CompensatorI;
extern Filter2p2z FilterVFF;
extern Filter2p2z FilterIRMS;

extern uint32_t vref; // voltage setpoint for booster
extern float VInv_rms;
extern float VInvSq_rms;
extern float I_rq;
extern float vbus;
extern float I_L;
extern float vac_rms;
extern uint8_t enabled;

void BoostInit();
void BoostSlowLoop();
void BoostFastLoop();
void BoostDisable();
void BoostEnable();

void DMATransferComplete_adc2(DMA_HandleTypeDef *hdma);
void DMATransferComplete_adc4(DMA_HandleTypeDef *hdma);
void DMATransferComplete_adc5(DMA_HandleTypeDef *hdma);


#endif /* INC_BOOST_H_ */
