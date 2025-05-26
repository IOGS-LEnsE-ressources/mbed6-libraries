/*  
 *  Structure of a main file for embedded project @ LEnsE
 *      Blinky on L476RG
 *
 *  This code allows to toggle the onboard LED at a period of 0.4s. 
 *****************************************************************
 *  Pinout :
 *      PA_5 - Input from Right Line sensor 
 *      PB_6 - Input from Center Line sensor 
 *      PA_7 - Input from Left Line sensor 
 *****************************************************************
 *  Tested with Nucleo L476RG board / Mbed OS 6
 *****************************************************************
 *  Author : J. VILLEMEJANE / LEnsE - Creation 2025/01/28
 *****************************************************************
 *  LEnsE / https://lense.institutoptique.fr/
 *      Based on Mbed OS 6 example : mbed-os-example-blinky-baremetal
 */

#include "mbed.h"

InterruptIn		line_R(PB_12);
InterruptIn		line_C(PB_6);
InterruptIn		line_L(PA_7);

int line_r_val, line_c_val, line_l_val;

int main()
{
		printf("Hello L476RG - LEnsE !!\r\n");

    while(1)
    {
				line_r_val = line_R;
				line_c_val = line_C;
				line_l_val = line_L;
				printf("L = %d - C = %d - R = %d \r\n", line_l_val, line_c_val, line_r_val); 
        thread_sleep_for(100);
    }
}