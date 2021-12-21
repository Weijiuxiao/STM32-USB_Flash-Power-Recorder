/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define Key_down_Pin GPIO_PIN_13
#define Key_down_GPIO_Port GPIOC
#define I_4A_sample_Pin GPIO_PIN_1
#define I_4A_sample_GPIO_Port GPIOA
#define I_100mA_sample_Pin GPIO_PIN_2
#define I_100mA_sample_GPIO_Port GPIOA
#define I_SW_100mA_Pin GPIO_PIN_3
#define I_SW_100mA_GPIO_Port GPIOA
#define I_SW_4A_Pin GPIO_PIN_4
#define I_SW_4A_GPIO_Port GPIOA
#define Bat_sample_Pin GPIO_PIN_5
#define Bat_sample_GPIO_Port GPIOA
#define USBA_BAT_SW_Pin GPIO_PIN_6
#define USBA_BAT_SW_GPIO_Port GPIOA
#define Uin_sample_Pin GPIO_PIN_7
#define Uin_sample_GPIO_Port GPIOA
#define Key_up_Pin GPIO_PIN_1
#define Key_up_GPIO_Port GPIOB
#define Key_enter_Det_Pin GPIO_PIN_10
#define Key_enter_Det_GPIO_Port GPIOB
#define PWR_EN_Pin GPIO_PIN_11
#define PWR_EN_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_12
#define SD_CS_GPIO_Port GPIOB
#define SD_SCK_Pin GPIO_PIN_13
#define SD_SCK_GPIO_Port GPIOB
#define SD_MISO_Pin GPIO_PIN_14
#define SD_MISO_GPIO_Port GPIOB
#define SD_MOSI_Pin GPIO_PIN_15
#define SD_MOSI_GPIO_Port GPIOB
#define USBA_SD_SW_Pin GPIO_PIN_8
#define USBA_SD_SW_GPIO_Port GPIOA
#define BT_RX_Pin GPIO_PIN_9
#define BT_RX_GPIO_Port GPIOA
#define BT_TX_Pin GPIO_PIN_10
#define BT_TX_GPIO_Port GPIOA
#define TFT_SW_Pin GPIO_PIN_15
#define TFT_SW_GPIO_Port GPIOA
#define TFT_SCL_Pin GPIO_PIN_3
#define TFT_SCL_GPIO_Port GPIOB
#define TFT_RES_Pin GPIO_PIN_4
#define TFT_RES_GPIO_Port GPIOB
#define TFT_SDA_Pin GPIO_PIN_5
#define TFT_SDA_GPIO_Port GPIOB
#define TFT_RS_Pin GPIO_PIN_6
#define TFT_RS_GPIO_Port GPIOB
#define TFT_CS_Pin GPIO_PIN_7
#define TFT_CS_GPIO_Port GPIOB
#define RTC_SCL_Pin GPIO_PIN_8
#define RTC_SCL_GPIO_Port GPIOB
#define RTC_SDA_Pin GPIO_PIN_9
#define RTC_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
