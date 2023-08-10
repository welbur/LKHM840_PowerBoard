/**
  ****************************(C) COPYRIGHT 2021 Boring_TECH*********************
  * @file       BSP_spi.c/h
  * @brief      ��HAL��SPI�������ж��η�װ������Ӧ���������е���
  * @note
  * @history
  *  Version    Date            Author          Modification
  *  V3.0.0     2020.7.14     	              	1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2021 Boring_TECH*********************
  */
#include "MSP_SPI.h"

#ifdef PowerBoard_ACS37800
SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI1_MODE;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES; // SPI_DIRECTION_1LINE;                         //SPI_DIRECTION_2LINES
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;				  // SPI_POLARITY_LOW
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;					  // SPI_PHASE_1EDGE
	hspi1.Init.NSS = SPI_NSS_SOFT;							  // SPI_NSS_HARD_OUTPUT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; // SPI_BAUDRATEPRESCALER_256
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10; // 7
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		LOG("error spi");		//Error_Handler();
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (spiHandle->Instance == SPI1)
	{
		/* SPI1 clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();
		SPI1_GPIO_CLK_ENABLE();				//__HAL_RCC_GPIOA_CLK_ENABLE();
		/**
 		 * @brief SPI1 的GPIO 引脚 
		 *	PB3     ------> SPI1_SCK
 		 *	PB4     ------> SPI1_MISO
		 *	PB5     ------> SPI1_MOSI
		 */
		GPIO_InitStruct.Pin = SPI1_SCK_PIN | SPI1_MISO_PIN | SPI1_MOSI_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;				// GPIO_PULLUP;     //GPIO_NOPULL
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM; // GPIO_SPEED_FREQ_LOW;	//GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
		/* NVIC for SPI */
		HAL_NVIC_SetPriority(SPI1_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle)
{
	if (spiHandle->Instance == SPI1)
	{
		/* Peripheral clock disable */
		//__HAL_RCC_SPI1_CLK_DISABLE();
		__HAL_RCC_SPI1_FORCE_RESET();
		__HAL_RCC_SPI1_RELEASE_RESET();
		/**SPI1 GPIO Configuration
		PB3     ------> SPI1_SCK
		PB4     ------> SPI1_MISO
		PB5     ------> SPI1_MOSI
		*/
		HAL_GPIO_DeInit(SPI1_GPIO_PORT, SPI1_SCK_PIN | SPI1_MISO_PIN | SPI1_MOSI_PIN);
	}
}

#if 0
void SPITransfer_GPIO_Init(void)
{
	/*******************************************      用于chip cs信号 先初始化需要用到的GPIO引脚      *************************************/
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    /**CS GPIO Configuration
    PA0     ------> CS1
    PA1     ------> CS2
    PA2     ------> CS3
    PA3     ------> CS4
    PA4     ------> CS5
    PA5     ------> CS6
    PA6     ------> CS7
    PA7     ------> CS8
    PC4     ------> CS9
    */
	CHIP_SPI1_CS1_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS1_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS2_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS2_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS3_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS3_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS4_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS4_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS5_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS5_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS6_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS6_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS7_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS7_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS8_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS8_Port, &GPIO_InitStruct);
	CHIP_SPI1_CS9_CLK_ENABLE();
	GPIO_InitStruct.Pin = CHIP_SPI1_CS9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CHIP_SPI1_CS9_Port, &GPIO_InitStruct);
	/*******************************************       将所有cs引脚都默认设为高电平     *************************************/
	HAL_GPIO_WritePin(CHIP_SPI1_CS1_Port, CHIP_SPI1_CS1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS2_Port, CHIP_SPI1_CS2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS3_Port, CHIP_SPI1_CS3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS4_Port, CHIP_SPI1_CS4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS5_Port, CHIP_SPI1_CS5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS6_Port, CHIP_SPI1_CS6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS7_Port, CHIP_SPI1_CS7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS8_Port, CHIP_SPI1_CS8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CHIP_SPI1_CS9_Port, CHIP_SPI1_CS9, GPIO_PIN_SET);
}
#endif

uint8_t SPI1_CS_VALUE(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/**
 * @brief  MSP_SPI_write
 * @param  spiHandle: 指向哪个spi号
 * @param  cs: 指向Slave板的cs引脚
 * @param  txData: 指向需要发送数据的指针
 * @param  txLen: 需要发送数据的长度
 * @note   Master板 通过spi1发送数据给Slave板.
 * @retval 发送成功 返回 1； 发送失败 返回 0
 */

#if 1
uint8_t MSP_SPI_write(SPI_HandleTypeDef *spiHandle, uint8_t *txData, uint16_t txLen)
{
	for (uint16_t i = 0; i < txLen; i++)
	{
		//LOG("%d ", *(txData + i));
		if (HAL_SPI_Transmit(spiHandle, (txData + i), 1, 10) != HAL_OK)
			return 0;
	}
	return 1;
}
#endif
/**
 * @brief  MSP_SPI_read
 * @param  spiHandle: 指向哪个spi号
 * @param  cs: 指向Slave板的cs引脚
 * @param  rxData: 指向需要发送数据的指针
 * @param  rxLen: 需要发送数据的长度
 * @note   通过spi号接收指定数量的数据.
 * @retval 发送成功 返回 1； 发送失败 返回 0
 */
#if 1
uint8_t MSP_SPI_read(SPI_HandleTypeDef *spiHandle, uint8_t *rxData, uint16_t rxLen)
{
	for (uint16_t i = 0; i < rxLen; i++)
	{
		if (HAL_SPI_Receive(spiHandle, rxData, 1, 10) != HAL_OK)
		{
			// LOGE("spi MSP_SPI_read timeout....\r\n");
			return 0;
		}
		while (HAL_SPI_GetState(spiHandle) != HAL_SPI_STATE_READY)
		{
		}
	}
	return 1;
}
#endif

#endif

/**
 * @brief  TxRx Transfer completed callback.
 * @param  hspi: SPI handle
 * @note   This example shows a simple way to report end of Interrupt TxRx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	//LOG("spi rx callback\r\n");
	//sTxRxFlag = SpiRx_COMPLETE;
}
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	//LOGI("spi tx callback\r\n");
	//sTxRxFlag = SpiTx_COMPLETE;
}

/**
 * @brief  SPI error callbacks.
 * @param  hspi: SPI handle
 * @note   This example shows a simple way to report transfer error, and you can
 *         add your own implementation.
 * @retval None
 */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	LOG("spi error callback\r\n");
	//sTxRxFlag = SpiTxRx_ERROR;
	HAL_SPI_MspDeInit(hspi);
	HAL_SPI_MspInit(hspi);
}
