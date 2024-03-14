/**
  ****************************(C) COPYRIGHT 2021 Boring_TECH*********************
  * @file       BSP_USART.c/h
  * @brief      将HAL库串口函数进行二次封装，并在串口中断中接收数据
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
#include "MSP_USART.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;
UART_HandleTypeDef huart3;

/* USART1 init function */
void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 921600;   //115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)   //初始化串口的引脚定义，在HAL_UART_MspInit函数里面
  {
    LOG_error("uart1 init error");
    //Error_Handler();
  }
}

/* USART6 init function */
void MX_USART6_UART_Init(void)
{
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 921600;   //115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)   //初始化串口的引脚定义，在HAL_UART_MspInit函数里面
  {
    LOG_error("uart6 init error");
    //Error_Handler();
  }
}

/* USART3 init function */
void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 921600;   //115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)   //初始化串口的引脚定义，在HAL_UART_MspInit函数里面
  {
    LOG_error("uart3 init error");
    //Error_Handler();
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)     //串口1 作为与BaseBoard板通信的接口
  {
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
    USART1_GPIO_CLK_ENABLE();       //__HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9      ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = USART1_TX_PIN|USART1_RX_PIN;  //GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 10, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  }
  else if(uartHandle->Instance==USART6)     //串口1 作为与BaseBoard板通信的接口(备用)
  {
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();
    USART6_GPIO_CLK_ENABLE();       //__HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART6 GPIO Configuration
    PA11     ------> USART6_TX
    PA12     ------> USART6_RX
    */
    GPIO_InitStruct.Pin = USART6_TX_PIN|USART6_RX_PIN; 
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(USART6_GPIO_PORT, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 10, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  }
  else if(uartHandle->Instance==USART3)     //串口3 作为debug口，调试信息打印
  {
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
    USART3_GPIO_CLK_ENABLE();       //__HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = USART3_TX_PIN|USART3_RX_PIN;  //GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART3;
    HAL_GPIO_Init(USART3_GPIO_PORT, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 10, 3);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance==USART1)
  {
    /* Peripheral clock disable */
    USART1_GPIO_CLK_DISABLE();          //__HAL_RCC_USART2_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9      ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(USART1_GPIO_PORT, USART1_TX_PIN|USART1_RX_PIN); 

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  }
  else if(uartHandle->Instance==USART6)
  {
    /* Peripheral clock disable */
    USART6_GPIO_CLK_DISABLE();          //__HAL_RCC_USART2_CLK_DISABLE();

    /**USART6 GPIO Configuration
    PA11     ------> USART6_TX
    PA12     ------> USART6_RX
    */
    HAL_GPIO_DeInit(USART6_GPIO_PORT, USART6_TX_PIN|USART6_RX_PIN); 

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  }
  else if(uartHandle->Instance==USART3)
  {
    /* Peripheral clock disable */
    USART3_GPIO_CLK_DISABLE();          //__HAL_RCC_USART2_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(USART3_GPIO_PORT, USART3_TX_PIN|USART3_RX_PIN); 

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  }
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

