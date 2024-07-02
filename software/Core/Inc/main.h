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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define INT_IN_Pin GPIO_PIN_0
#define INT_IN_GPIO_Port GPIOC
#define INT_IN_EXTI_IRQn EXTI0_IRQn
#define I_PRI_COMP_Pin GPIO_PIN_2
#define I_PRI_COMP_GPIO_Port GPIOC
#define I_PRI_COMP_EXTI_IRQn EXTI2_IRQn
#define OCD_Pin GPIO_PIN_3
#define OCD_GPIO_Port GPIOC
#define VBUS_Pin GPIO_PIN_0
#define VBUS_GPIO_Port GPIOA
#define THERM1_Pin GPIO_PIN_1
#define THERM1_GPIO_Port GPIOA
#define THERM2_Pin GPIO_PIN_2
#define THERM2_GPIO_Port GPIOA
#define THERM3_Pin GPIO_PIN_3
#define THERM3_GPIO_Port GPIOA
#define I_L_Pin GPIO_PIN_5
#define I_L_GPIO_Port GPIOA
#define VAC_Pin GPIO_PIN_6
#define VAC_GPIO_Port GPIOA
#define SCR_OUT_Pin GPIO_PIN_0
#define SCR_OUT_GPIO_Port GPIOB
#define FAN_1_Pin GPIO_PIN_14
#define FAN_1_GPIO_Port GPIOB
#define FAN_2_Pin GPIO_PIN_15
#define FAN_2_GPIO_Port GPIOB
#define LED_IDRAW_Pin GPIO_PIN_6
#define LED_IDRAW_GPIO_Port GPIOC
#define LED_TEMP_Pin GPIO_PIN_8
#define LED_TEMP_GPIO_Port GPIOC
#define VAC_TRIG_Pin GPIO_PIN_9
#define VAC_TRIG_GPIO_Port GPIOC
#define VAC_TRIG_EXTI_IRQn EXTI9_5_IRQn
#define PFC_PWM_Pin GPIO_PIN_8
#define PFC_PWM_GPIO_Port GPIOA
#define RGB_1_Pin GPIO_PIN_6
#define RGB_1_GPIO_Port GPIOB
#define RGB_2_Pin GPIO_PIN_7
#define RGB_2_GPIO_Port GPIOB
#define RGB_3_Pin GPIO_PIN_8
#define RGB_3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
