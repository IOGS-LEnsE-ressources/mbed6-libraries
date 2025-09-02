/**
  ******************************************************************************
  * @file    Display/LCD_Paint/Inc/save.h 
  * @author  MCD Application Team
  * @brief   This file contains image used for LTDC application.   
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

/* */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IMAGES_H
#define __IMAGES_H

/* LEnsE Logo */
#include "image_output_logo_lense_0_0.h"
#include "image_output_logo_lense_0_200.h"
#include "image_output_logo_lense_120_0.h"
#include "image_output_logo_lense_120_200.h"

/* Bing'Optik Logo */
#include "image_output_logo_bingo_0_0.h"
#include "image_output_logo_bingo_0_200.h"
#include "image_output_logo_bingo_0_400.h"
#include "image_output_logo_bingo_0_600.h"
#include "image_output_logo_bingo_120_0.h"
#include "image_output_logo_bingo_120_200.h"
#include "image_output_logo_bingo_120_400.h"
#include "image_output_logo_bingo_120_600.h"
#include "image_output_logo_bingo_240_0.h"
#include "image_output_logo_bingo_240_200.h"
#include "image_output_logo_bingo_240_400.h"
#include "image_output_logo_bingo_240_600.h"
#include "image_output_logo_bingo_360_0.h"
#include "image_output_logo_bingo_360_200.h"
#include "image_output_logo_bingo_360_400.h"
#include "image_output_logo_bingo_360_600.h"


/* Numbers */
#include "image_output_1_1.h"
#include "image_output_2_1.h"
#include "image_output_3_1.h"
#include "image_output_4_1.h"
#include "image_output_5_1.h"
#include "image_output_6_1.h"
#include "image_output_7_1.h"
#include "image_output_8_1.h"
#include "image_output_9_1.h"

#define		IMAGE_WIDTH		200
#define		IMAGE_HEIGHT	120
#define		LOGO_WIDTH		800
#define		LOGO_HEIGHT		480
#define		IMAGE_WIDTH_B	IMAGE_WIDTH / 8
#define		COLOR_VARIATION	60


/* Colors from L432 */
const float R_trans[COLOR_VARIATION] = {
	1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1,
	0.1, 0.1, 0.07,0.06,0.04,0.02,0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
};

const float G_trans[COLOR_VARIATION] = {
	0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.65, 0.8, 0.9,
	0.9, 0.9, 0.8, 0.8, 0.75,0.75,0.74,0.72,0.71, 0.7,
	0.7, 0.6, 0.5, 0.4, 0.4, 0.3, 0.3, 0.2, 0.2, 0.2,
	0.2, 0.2,0.15,0.13,0.08, 0.06, 0.02, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.1, 0.1, 0.2, 0.3, 0.4, 0.5, 0.5, 0.6,
	0.6, 0.6, 0.5, 0.4, 0.3, 0.2, 0.2, 0.1, 0.0, 0.0
};


const float B_trans[COLOR_VARIATION] = {
	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
	0.0, 0.1, 0.1, 0.2, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
	0.7, 0.7, 0.7, 0.8, 0.8, 0.8, 0.9, 0.9, 0.9, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.1, 0.0,
	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};


#endif /* __SAVE_H */
