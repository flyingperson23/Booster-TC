/*
 * pwm.c
 *
 *  Created on: Jul 15, 2024
 *      Author: flyin
 */

#include <power/pwm.h>

void PWMInit() {
	HAL_COMP_Start(&hcomp1);
	HAL_COMP_Start(&hcomp3);

	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);

}

uint8_t ocdside = 0;
uint32_t disablepins = 0;
uint32_t delay = 0;
uint32_t capture = 0; // full period length

void TIM1_CC_IRQHandler(void) {
    if (TIM1->SR & (1 << 1)) { // channel 1 - input capture
    	TIM1->SR = ~TIM_SR_CC1IF;
    	if (!(COMP1->CSR & (1 << 30))) { // got cc for first halfwave
    		capture = TIM1->CCR1 << 1;
    		TIM1->CCR2 = capture - delay;
    		TIM1->ARR = capture;

    		TIM8->ARR = capture;
    		TIM8->CCR1 = TIM1->CCR1;
    	}
    }
    if (TIM1->SR & (1 << 2)) { // channel 2 - timing pwm
    	TIM1->SR = ~TIM_SR_CC2IF;
    	GPIOB->BSRR = disablepins;
    }
}


void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp){
	if (COMP3->CSR & (1 << 30)) { // if triggered
		if (ocdside) {
			disablepins = GDT2_DIS_Pin | GDT1_DIS_Pin << 16;
		} else {
			disablepins = GDT2_DIS_Pin << 16 | GDT1_DIS_Pin;
		}
	} else {
		disablepins = GDT2_DIS_Pin << 16 | GDT1_DIS_Pin << 16;
	}
}
