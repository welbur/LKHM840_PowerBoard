/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MSP_CAN.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
 
/* USER CODE END Header */
/* 设置波特率为：500k
 * hcan1.Init.Prescaler = 10
 * hcan1.Init.TimeSeg1 = CAN_BS1_8TQ
 * hcan1.Init.TimeSeg2 = CAN_BS2_1TQ
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MSP_CAN_H__
#define __MSP_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include "stm32f4xx_hal.h"
#include "LOG.h"
#include "PinConfig.h"
#include "PowerBoardConfig.h"
//#include "ErrorInfo.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_CAN2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __MSP_CAN_H__ */

