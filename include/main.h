/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LOG.h"
#include "MSP_GPIO.h"
#include "MSP_USART.h"
#include "MSP_SPI.h"
#include "SPITransfer_C.h"
#include "stdio.h"
#include "SlaveBoardConfig.h"
#ifdef RTOS_enable
#include "cmsis_os.h"
#endif
#include "dma.h"

#if defined(RS485_Board)
  #include "Modbus.h"
#elif defined(D_I_Board)
  #include "ISO1I813T_DI.h"
#elif defined(D_Q_Board)
  #include "ISO2H825V25_DQ.h"
//#else
//  #error "Slave Board select error!"
#endif

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
// 位操作函数
//#define SET_BIT(reg, bit)   ((reg) |= (1 << (bit)))
//#define CLEAR_BIT(reg, bit) ((reg) &= ~(1 << (bit)))
#define isBIT_SET(reg, bit)  ((reg) & (1 << (bit)))         //(reg & (1 << bit)) >> bit
//#define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit)))

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  

extern uint8_t testi;

#ifdef RS485_Board
extern modbusHandler_t ModbusH;
extern uint16_t ModbusDATA[128];
#endif
#if defined(D_I_Board) || defined(D_Q_Board)
extern CHIPHandler_t CHIPH[4];
#endif


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
