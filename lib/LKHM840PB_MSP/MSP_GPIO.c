/**
  ****************************(C) COPYRIGHT 2021 Boring_TECH*********************
  * @file       BSP_GPIO.c/h
  * @brief      GPIO的二次封装
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
#include "MSP_GPIO.h"

// uint8_t DefaultBoardID = 0;
HAL_TickFreqTypeDef TickFreq = HAL_TICK_FREQ_DEFAULT; /* 1KHz */

/** Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 * Free pins are configured automatically as Analog (this feature is enabled through
 * the Code Generation settings)
 */

void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

#if defined(DEVBoard) || defined(DEVBoardYD)
	/*Configure GPIO pin : 设置按键 */
	GPIO_InitStruct.Pin = KEY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; // GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins :设置led */
	GPIO_InitStruct.Pin = RED_Pin | GREEN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RED_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET);
#endif
	/*Configure GPIO pins :设置Workled */
	GPIO_InitStruct.Pin = WorkLed_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(WorkLed_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(WorkLed_GPIO_Port, WorkLed_Pin, GPIO_PIN_SET);


}

/**
 * @brief  Configures EXTI Line in interrupt mode
 * @param  None
 * @retval None
 */
void EXTILine_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

// 设置按键的中断 PB3
#if defined(DEVBoard) || defined(DEVBoardYD)
	KEY_Pin_CLK_ENABLE();
	GPIO_InitStruct.Pin = KEY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(KEY_GPIO_Port, KEY_Pin, 1);
	HAL_NVIC_SetPriority(KEY_Pin_EXTI_IRQn, 2, 10);
	HAL_NVIC_EnableIRQ(KEY_Pin_EXTI_IRQn);
#endif

	/*Configure GPIO pins : PB0 PB1 PB2 PB3 PB4 PB5 PB10 PB12 PB13 */
	GPIO_InitStruct.Pin = ZRC_IN1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN1_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN1_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN1_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN2_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN2_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN2_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN3_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN3_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN3_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN4_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN4_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN4_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN5_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN5_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN5_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN6_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN6_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN6_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN7_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN7_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN7_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN8_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN8_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN8_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN8_Pin_EXTI_IRQn);

	GPIO_InitStruct.Pin = ZRC_IN9_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ZRC_IN9_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(ZRC_IN9_Pin_EXTI_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ZRC_IN9_Pin_EXTI_IRQn);

}


// 配置文件在.h文件中
