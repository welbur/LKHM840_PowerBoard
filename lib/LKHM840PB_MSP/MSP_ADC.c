
#include "MSP_ADC.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
void MX_ADC1_Init(void)
{

	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	ADC_ChannelConfTypeDef sConfig = {0};

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		LOG("adc init error!\r\n"); // Error_Handler();
	}

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = 2;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = 3;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_3;
	sConfig.Rank = 4;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 5;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_5;
	sConfig.Rank = 6;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 7;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_7;
	sConfig.Rank = 8;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	sConfig.Channel = ADC_CHANNEL_14;
	sConfig.Rank = 9;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

/**
 * @brief ADC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hadc: ADC handle pointer
 * @retval None
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (hadc->Instance == ADC1)
	{
		/* USER CODE BEGIN ADC1_MspInit 0 */

		/* USER CODE END ADC1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**ADC1 GPIO Configuration
		PA0     ------> ADC1_IN0
		PA1     ------> ADC1_IN1
		PA2     ------> ADC1_IN2
		PA3     ------> ADC1_IN3
		PA4     ------> ADC1_IN4
		PA5     ------> ADC1_IN5
		PA6     ------> ADC1_IN6
		PA7     ------> ADC1_IN7
		PC4     ------> ADC1_IN14
		*/
		GPIO_InitStruct.Pin = ADC1_IN0_Pin | ADC1_IN1_Pin | ADC1_IN2_Pin | ADC1_IN3_Pin | ADC1_IN4_Pin | ADC1_IN5_Pin | ADC1_IN6_Pin | ADC1_IN7_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(ADC1_IN0_IN7_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = ADC1_IN14_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(ADC1_IN14_Port, &GPIO_InitStruct);

		// 初始化DMA
		hdma_adc1.Instance = DMA2_Stream0;
		hdma_adc1.Init.Channel = DMA_CHANNEL_0;
		hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;	//DMA_PDATAALIGN_HALFWORD
		hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;		//DMA_PDATAALIGN_HALFWORD
		hdma_adc1.Init.Mode = DMA_CIRCULAR;							//DMA_NORMAL
		hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
		hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&hdma_adc1);

		// 将DMA与ADC关联起来
		__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc1);

	}
}

/**
 * @brief ADC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hadc: ADC handle pointer
 * @retval None
 */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
	if (hadc->Instance == ADC1)
	{
		/* USER CODE BEGIN ADC1_MspDeInit 0 */

		/* USER CODE END ADC1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_ADC1_CLK_DISABLE();

		/**ADC1 GPIO Configuration
		PA0     ------> ADC1_IN0
		PA1     ------> ADC1_IN1
		PA2     ------> ADC1_IN2
		PA3     ------> ADC1_IN3
		PA4     ------> ADC1_IN4
		PA5     ------> ADC1_IN5
		PA6     ------> ADC1_IN6
		PA7     ------> ADC1_IN7
		PC4     ------> ADC1_IN14
		*/
		HAL_GPIO_DeInit(ADC1_IN0_IN7_Port, ADC1_IN0_Pin | ADC1_IN1_Pin | ADC1_IN2_Pin | ADC1_IN3_Pin | ADC1_IN4_Pin | ADC1_IN5_Pin | ADC1_IN6_Pin | ADC1_IN7_Pin);

		HAL_GPIO_DeInit(ADC1_IN14_Port, ADC1_IN14_Pin);

    	/* ADC1 DMA DeInit */
    	HAL_DMA_DeInit(hadc->DMA_Handle);
		/* USER CODE BEGIN ADC1_MspDeInit 1 */

		/* USER CODE END ADC1_MspDeInit 1 */
	}
}
