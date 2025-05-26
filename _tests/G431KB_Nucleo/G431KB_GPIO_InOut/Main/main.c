/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "main.h"

GPIO_PinState pinA9;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
	initMCU();

	/* User Initialization*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	
  /* Infinite loop */
  while (1)
  {
		// Read Input A9
		pinA9 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
		// Update Output B8 - LED1
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, pinA9);
		
    HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_6);
    HAL_Delay (10);		// ms
  }
}
