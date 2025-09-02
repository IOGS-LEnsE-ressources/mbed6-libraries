/**
  ******************************************************************************
  * @file    Display/LCD_Paint/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32469i_discovery.h"
#include "stm32469i_discovery_lcd.h"
#include "stm32469i_discovery_ts.h"
#include "stm32469i_discovery_sdram.h"
#include <stdlib.h>
#include <stdio.h>

#include "PixelArray.h"
#include "WS2812.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Alias for LCD_FB_START_ADDRESS : frame buffer displayed on LCD */
#define LCD_FRAME_BUFFER              LCD_FB_START_ADDRESS

#define WVGA_RES_X                    800
#define WVGA_RES_Y                    480

#define LCD_SCREEN_WIDTH              WVGA_RES_X
#define LCD_SCREEN_HEIGHT             WVGA_RES_Y

#define ARGB8888_BYTE_PER_PIXEL       4
#define RGB888_BYTE_PER_PIXEL         3

#define	LED_STRIP_1_NB				10


#define RANDOM_Pin GPIO_PIN_2
#define RANDOM_GPIO_Port GPIOA
#define MODE_Pin GPIO_PIN_14
#define MODE_GPIO_Port GPIOB
#define SYNC_Pin GPIO_PIN_7
#define SYNC_GPIO_Port GPIOA
#define SYNC_EXTI_IRQn EXTI9_5_IRQn
#define SYNC0_Pin GPIO_PIN_6
#define SYNC0_GPIO_Port GPIOA
#define SYNC0_EXTI_IRQn EXTI9_5_IRQn
#define LED_SW1_Pin GPIO_PIN_11
#define LED_SW1_GPIO_Port GPIOG
#define LED_SW2_Pin GPIO_PIN_10
#define LED_SW2_GPIO_Port GPIOG


/* Buffer LCD Converted to RGB888 in SDRAM in order to be copied to SD Card   */
/* Starts directly at end of LCD frame buffer                                 */
#define CONVERTED_FRAME_BUFFER        LCD_FRAME_BUFFER + (LCD_SCREEN_WIDTH * LCD_SCREEN_HEIGHT * ARGB8888_BYTE_PER_PIXEL)

/* Imported globals ----------------------------------------------------------*/
extern TS_StateTypeDef  TS_State;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t  Touchscreen_Calibration(void);
uint16_t TouchScreen_Get_Calibrated_X(uint16_t x);
uint16_t TouchScreen_Get_Calibrated_Y(uint16_t y);
uint8_t  TouchScreen_IsCalibrationDone(void);

#endif /* __MAIN_H */
