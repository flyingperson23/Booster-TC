/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_HRTIM_MspPostInit(HRTIM_HandleTypeDef *hhrtim);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GDT1A_Pin GPIO_PIN_13
#define GDT1A_GPIO_Port GPIOC
#define FAN_EN_Pin GPIO_PIN_14
#define FAN_EN_GPIO_Port GPIOC
#define CS_FAN_Pin GPIO_PIN_15
#define CS_FAN_GPIO_Port GPIOC
#define I_PRI_Pin GPIO_PIN_0
#define I_PRI_GPIO_Port GPIOA
#define CTP_1_Pin GPIO_PIN_1
#define CTP_1_GPIO_Port GPIOA
#define THERM2_Pin GPIO_PIN_2
#define THERM2_GPIO_Port GPIOA
#define THERM1_Pin GPIO_PIN_3
#define THERM1_GPIO_Port GPIOA
#define CTM_1_Pin GPIO_PIN_4
#define CTM_1_GPIO_Port GPIOA
#define CTM_2_Pin GPIO_PIN_5
#define CTM_2_GPIO_Port GPIOA
#define LED_VBUS_Pin GPIO_PIN_6
#define LED_VBUS_GPIO_Port GPIOA
#define CTP_2_Pin GPIO_PIN_7
#define CTP_2_GPIO_Port GPIOA
#define LED_TMP_Pin GPIO_PIN_0
#define LED_TMP_GPIO_Port GPIOB
#define LED_I_IN_Pin GPIO_PIN_1
#define LED_I_IN_GPIO_Port GPIOB
#define INT_Pin GPIO_PIN_2
#define INT_GPIO_Port GPIOB
#define TX_Pin GPIO_PIN_10
#define TX_GPIO_Port GPIOB
#define VAC_SENSE_Pin GPIO_PIN_11
#define VAC_SENSE_GPIO_Port GPIOB
#define MODE_IN_Pin GPIO_PIN_12
#define MODE_IN_GPIO_Port GPIOB
#define I_L_Pin GPIO_PIN_14
#define I_L_GPIO_Port GPIOB
#define VBUS_SENSE_Pin GPIO_PIN_8
#define VBUS_SENSE_GPIO_Port GPIOA
#define PFC_Pin GPIO_PIN_9
#define PFC_GPIO_Port GPIOA
#define DRIVE_EN_Pin GPIO_PIN_10
#define DRIVE_EN_GPIO_Port GPIOA
#define CS_DRIVE_Pin GPIO_PIN_11
#define CS_DRIVE_GPIO_Port GPIOA
#define SCR_Pin GPIO_PIN_12
#define SCR_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define TDI_Pin GPIO_PIN_15
#define TDI_GPIO_Port GPIOA
#define TDO_Pin GPIO_PIN_3
#define TDO_GPIO_Port GPIOB
#define GDT2B_Pin GPIO_PIN_4
#define GDT2B_GPIO_Port GPIOB
#define GDT2_DIS_Pin GPIO_PIN_5
#define GDT2_DIS_GPIO_Port GPIOB
#define GDT2A_Pin GPIO_PIN_6
#define GDT2A_GPIO_Port GPIOB
#define GDT1_DIS_Pin GPIO_PIN_7
#define GDT1_DIS_GPIO_Port GPIOB
#define RX_Pin GPIO_PIN_8
#define RX_GPIO_Port GPIOB
#define GDT1B_Pin GPIO_PIN_9
#define GDT1B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc4;
extern ADC_HandleTypeDef hadc5;

extern COMP_HandleTypeDef hcomp1;
extern COMP_HandleTypeDef hcomp2;
extern COMP_HandleTypeDef hcomp3;
extern COMP_HandleTypeDef hcomp6;
extern COMP_HandleTypeDef hcomp7;

extern DAC_HandleTypeDef hdac2;
extern DAC_HandleTypeDef hdac3;

extern FMAC_HandleTypeDef hfmac;

extern HRTIM_HandleTypeDef hhrtim1;

extern SPI_HandleTypeDef hspi2;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

extern UART_HandleTypeDef huart3;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
