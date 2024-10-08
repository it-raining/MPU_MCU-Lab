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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include "global.h"
#include "swTimer.h"
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN1_Pin GPIO_PIN_1
#define BTN1_GPIO_Port GPIOA
#define BTN2_Pin GPIO_PIN_2
#define BTN2_GPIO_Port GPIOA
#define BTN3_Pin GPIO_PIN_3
#define BTN3_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_4
#define EN0_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_5
#define EN1_GPIO_Port GPIOA
#define EN2_Pin GPIO_PIN_6
#define EN2_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_7
#define EN3_GPIO_Port GPIOA
#define LED_RED_1_Pin GPIO_PIN_1
#define LED_RED_1_GPIO_Port GPIOB
#define LED_GREEN_1_Pin GPIO_PIN_2
#define LED_GREEN_1_GPIO_Port GPIOB
#define LED_RED_4_Pin GPIO_PIN_10
#define LED_RED_4_GPIO_Port GPIOB
#define LED_GREEN_4_Pin GPIO_PIN_11
#define LED_GREEN_4_GPIO_Port GPIOB
#define LED_AMBER_4_Pin GPIO_PIN_12
#define LED_AMBER_4_GPIO_Port GPIOB
#define LED_PINK_Pin GPIO_PIN_8
#define LED_PINK_GPIO_Port GPIOA
#define SEG_0_Pin GPIO_PIN_9
#define SEG_0_GPIO_Port GPIOA
#define SEG_1_Pin GPIO_PIN_10
#define SEG_1_GPIO_Port GPIOA
#define SEG_2_Pin GPIO_PIN_11
#define SEG_2_GPIO_Port GPIOA
#define SEG_3_Pin GPIO_PIN_12
#define SEG_3_GPIO_Port GPIOA
#define SEG_4_Pin GPIO_PIN_13
#define SEG_4_GPIO_Port GPIOA
#define SEG_5_Pin GPIO_PIN_14
#define SEG_5_GPIO_Port GPIOA
#define SEG_6_Pin GPIO_PIN_15
#define SEG_6_GPIO_Port GPIOA
#define LED_AMBER_1_Pin GPIO_PIN_3
#define LED_AMBER_1_GPIO_Port GPIOB
#define LED_RED_2_Pin GPIO_PIN_4
#define LED_RED_2_GPIO_Port GPIOB
#define LED_GREEN_2_Pin GPIO_PIN_5
#define LED_GREEN_2_GPIO_Port GPIOB
#define LED_AMBER_2_Pin GPIO_PIN_6
#define LED_AMBER_2_GPIO_Port GPIOB
#define LED_RED_3_Pin GPIO_PIN_7
#define LED_RED_3_GPIO_Port GPIOB
#define LED_GREEN_3_Pin GPIO_PIN_8
#define LED_GREEN_3_GPIO_Port GPIOB
#define LED_AMBER_3_Pin GPIO_PIN_9
#define LED_AMBER_3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
