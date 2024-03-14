/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention      : LKHM840 PowerBoard
 *                   2023-08-11  V0.0.3
 *
 *       1、usart1用于与主控板通信用，采用私有背板协议，采用RS485方式
 *           PA9     ------> USART1_TX
 *           PA10    ------> USART1_RX
 *           BaudRate = 921600
 *
 *       2、usart6用于与主控板通信用，第二个RS485，备用
 *           PA11     ------> USART6_TX
 *           PA12     ------> USART6_RX
 *           BaudRate = 921600
 *
 *       3、usart3用于打印测试信息
 *           PC10    ------> USART3_TX
 *           PC11    ------> USART3_RX
 *           BaudRate = 921600
 *
 * 		 4、通过tim输出pwm信号，或者是相位角控制信号
 *  		 *  TIM3 GPIO Configuration
 *			    PC6     ------> TIM3_CH1
 *		 	    PC7     ------> TIM3_CH2
 *			    PC8     ------> TIM3_CH3
 *			    PC9     ------> TIM3_CH4
 *			 *  TIM4 GPIO Configuration
 *			    PB6     ------> TIM4_CH1
 *			    PB7     ------> TIM4_CH2
 *			    PB8     ------> TIM4_CH3
 *			    PB9     ------> TIM4_CH4
 *			 *  TIM12 GPIO Configuration
 *		  	    PB15     ------> TIM12_CH2
 *
 *	 	 5、过零检测信号输入
 * 				PB0      ------> ZRC_IN1
 * 				PB1      ------> ZRC_IN2
 * 				PB2      ------> ZRC_IN3
 * 				PB3      ------> ZRC_IN4
 * 				PB4      ------> ZRC_IN5
 * 				PB5      ------> ZRC_IN6
 * 				PB10     ------> ZRC_IN7
 * 				PB12     ------> ZRC_IN8
 * 				PB13     ------> ZRC_IN9
 * 
 * 		 6、ADC信号进入 （使用MLX91220时采用）
 *     		 *  ADC1 GPIO Configuration
 *			    PA0     ------> ADC1_IN0
 *			    PA1     ------> ADC1_IN1
 *			    PA2     ------> ADC1_IN2
 *			    PA3     ------> ADC1_IN3
 *			    PA4     ------> ADC1_IN4
 *			    PA5     ------> ADC1_IN5
 *			    PA6     ------> ADC1_IN6
 *			    PA7     ------> ADC1_IN7
 *			    PC4     ------> ADC1_IN14
 *
 * 		 7、热电偶转换芯片 简单SPI接口（只读）
 * 				
 * 
 *       8、WorkLed, BoardID
 *              PC0     ------> WorkLed
 *  			PC1     ------> BoardID_1
 * 				PC2     ------> BoardID_2
 * 
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "PowerBoardConfig.h"
#include "stm32f4xx_hal.h"

	/* Private includes ----------------------------------------------------------*/
	/* USER CODE BEGIN Includes */

#include "MSP_GPIO.h"
#include "MSP_USART.h"
#include "MSP_ADC.h"
#include "MSP_TIM.h"
#include "MSP_DMA.h"

#include "PinConfig.h"

#include "LOG.h"

#include "BackPanelTrans.h"
#include "MLX91220.h"
#include "FrameFormat.h"



#define Default_SlaveTranstoMasterMode_Trigger 		1
#define Default_SlaveTranstoMasterMode_Loop 		  2

#define Default_SlaveTranstoMasterMode_Loop_Time 	50

#define DefaultbpCMDLen                  4     //有效数据(4)
#define DefaultbpDATALen                 120   //有效数据(120)


// 复制一个数组到另一个数组
#define COPY_ARRAY(dest, src, len) memcpy(dest, src, (len) * sizeof((src)[0]))
// 板ID位操作函数
// #define Enable_Board(reg, bit)   ((reg) |= (1 << (bit)))
// #define Disable_Baord(reg, bit) ((reg) &= ~(1 << (bit)))
#define whichBoard_Enable(reg, bit) ((reg) & (1 << (bit))) //(reg & (1 << bit)) >> bit
// #define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit)))


#define SlaveTranstoMasterMode_Trigger 		0
#define SlaveTranstoMasterMode_Loop 		1

/**
 * @struct slaveboardINFOHandler_t
 * @param boardID ： 从板的ID，由硬件引脚bID0和bID1决定
 * @param SlaveTranstoMasterMode : 从板发送数据给主板的模式，有两种 触发模式 和 循环模式
 * 								触发模式：设置触发条件(电流阀值或者功率阀值等)，然后主动上报给主板
 * 								循环模式：从板读取完芯片的数据后，保存到指定寄存器，然后等待主板过来读取。
 * SPITrans handler structure
 * 用于 spi trans的初始化参数
 */
typedef struct
{
	uint8_t 			boardID;				//从板发给主板的信息1 ： 从板ID
	uint8_t				BackPanelDataLen;		//从板发给主板的信息2 ： 从办的数据长度(包括 包头+有效数据+包尾)
	uint8_t				SlaveTranstoMasterMode;	//主板发给从办的信息1 : 触发模式和循环模式
	uint16_t			LoopTimeV;				//主板发给从办的信息2 ：循环模式下的轮询时间间隔
} slaveboardINFOHandler_t;

slaveboardINFOHandler_t sbINFOH;

//extern uint8_t		_slaveBoardID;
extern uint8_t 			DevButton; 
//extern uint8_t			SPI2_CS_Trig;

uint8_t getBoardID(void);
extern void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
