/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
#define Load_channel_num   9
/* Private variables ---------------------------------------------------------*/


BackPanelHandler_t BackPanelH;
PowerMonitorHandler_t PowerMonitorH;


float AC_Inow[Load_channel_num];
float AC_Irms[Load_channel_num];
float AC_Itrms[Load_channel_num];

uint32_t TransLastTime = 0;
uint32_t BPTrans_period = 10;

/*定义数据类型*/

uint8_t LoadState_DataType      = 1;
uint8_t	Inow_DataType		    = 2;   
uint8_t	Irms_DataType		    = 3;
uint8_t Itrms_DataType		    = 4;

#ifdef RS485_Board
/*modbus相关参数*/
modbusHandler_t ModbusH;
uint16_t ModbusDATA[128];
#endif

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
//void MX_FREERTOS_Init(void);
void Error_Handler(void);

//void SPI1_CS_GPIO_Init(void);
/* Private user code ---------------------------------------------------------*/
/**/

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	EXTILine_Config();
	MX_DMA_Init();
	
	MX_USART1_UART_Init();
	MX_USART6_UART_Init();
	MX_USART3_UART_Init();

//	MX_TIM3_Init();
//	MX_TIM4_Init();
//	MX_TIM12_Init();
//	MX_TIM6_Init();
	LOG("Initialize all configured peripherals OK!\r\n");
	printf("Initialize all configured peripherals OK!\r\n");



	/* 设置Power Monitor的相关参数 */
//	PowerMonitorH.AC_freq = 50;
//	PowerMonitorH.ADC_channel_num = Load_channel_num;   //9个电流检测芯片MLX91220，采用9路ADC去采样
//	PowerMonitorH.ADC_conv_period = 10;		//表示10us读取一次adc的数值
	
//	PowerMonitor_Init(&PowerMonitorH);
//	FiltersInit();
//	calibrate();		//获取基准零值，用于校准电流值
	/* PowerMonitor的设置和初始化已完成，等待开启PowerMonitor_Process */

	/* 设置BackPanelTrans的相关参数 */
//	BackPanelH.port = &huart1;
//	BackPanelH.BoardID = getBoardID();
//	BackPanelH.RecvBuf = BPRecvData;
//	BackPanelH.RecvBufSize = sizeof(BPRecvData) / sizeof(BPRecvData[0]);
//	BackPanelH.SendBuf = BPSendData;
//	BackPanelH.SendBufSize = sizeof(BPSendData) / sizeof(BPSendData[0]);
	
//	BackPanelProtocol_Init(&BackPanelH);


#ifdef RS485_Board
	/* Modbus 从站初始化Slave initialization */
	ModbusH.uModbusType = MB_SLAVE;
	ModbusH.port = &huart2;
	ModbusH.u8id = 1; // slave ID,  For master it must be 0
	ModbusH.u16timeOut = 1000;
	ModbusH.EN_Port = NULL; // No RS485   //ModbusH.EN_Port = NULL;
	ModbusH.EN_Pin = 0;
	// ModbusH2.EN_Port = LD2_GPIO_Port; // RS485 Enable
	// ModbusH2.EN_Pin = LD2_Pin; // RS485 Enable
	ModbusH.u16regs = ModbusDATA;
	ModbusH.u16regsize = sizeof(ModbusDATA) / sizeof(ModbusDATA[0]);
	ModbusH.xTypeHW = USART_HW_DMA;
	LOGI("start modbus rtu master...\r\n");
	// Initialize Modbus library
	ModbusInit(&ModbusH);
	// Start capturing traffic on serial Port
	ModbusStart(&ModbusH);
	/***********/
#endif
	while (1){
		//HAL_Delay(1000);
		LED_G(1);
		LED_R(0);
		LOG("loop\n");
	}
#if 0
	while (1) {
		BackPanelProtocol_Process();
		PowerMonitor_process();
		//getAC_Inow(AC_Inow);
		//getAC_Irms(AC_Irms);
		if ((getAC_Inow(AC_Inow) == 1) || (getAC_Irms(AC_Irms) == 1)) {
			uint8_t LoadData[128];
			uint16_t idx = 0;
			memcpy(LoadData + idx, &Inow_DataType, 1);
			idx += 1;

			for (int i = 0; i < Load_channel_num; i++) {
				memcpy(LoadData + idx, &AC_Inow[i], 4);
				idx += 4;
			}

			memcpy(LoadData + idx, &Irms_DataType, 1);
			idx += 1;

			for (int i = 0; i < Load_channel_num; i++) {
				memcpy(LoadData + idx, &AC_Irms[i], 4);
				idx += 4;
			}

			fillTransData(LoadData, idx);
		}
	}
#endif
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 100000000
  *            HCLK(Hz)                       = 100000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  * 		   /////////HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 100
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
#if 1
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 100;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
	{
		Error_Handler();
	}
}
#endif

#ifdef UartPrintf
PUTCHAR_PROTOTYPE
{
	/* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 1);
	return ch;
}
#endif




#if 1
/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}
}
#endif


#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   tex: LOGE("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
