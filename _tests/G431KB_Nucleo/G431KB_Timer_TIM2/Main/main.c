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
#include "tim.h"

/* ISR for TIM2 timer */
// ARR = 10 / PSC = 4250 / F_CLK = 85 MHz
// f_TIM2 = F_CLK / ((ARR+1)(PSC+1))
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
}


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
	change_TIM2_PSC(1);
	change_TIM2_ARR(1);
	
	/* Start Timer TIM2 */
	HAL_TIM_Base_Start_IT(&htim2);
	
  /* Infinite loop */
  while (1)
  {
    HAL_Delay (10);		// ms
		//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
  }
}
