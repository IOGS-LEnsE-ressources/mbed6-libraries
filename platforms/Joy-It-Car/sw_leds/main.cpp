/*  
 *  Structure of a main file for embedded project @ LEnsE
 *      Blinky on L476RG
 *
 *  This code allows to toggle the onboard LED at a period of 0.4s. 
 *****************************************************************
 *  Pinout :
 *      PC_7 - Output connected to LED1 of the board (low state)
 *      PB_13 - Output connected to LED2 of the board (high state)
 *      PA_11 - Input connected to SW1 of the board
 *      PA_12 - Input connected to SW2 of the board
 *      PC_13 - Input connected to User Button of the Nucleo board
 *****************************************************************
 *  Tested with Nucleo L476RG board / Mbed OS 6
 *****************************************************************
 *  Author : J. VILLEMEJANE / LEnsE - Creation 2025/01/28
 *****************************************************************
 *  LEnsE / https://lense.institutoptique.fr/
 *      Based on Mbed OS 6 example : mbed-os-example-blinky-baremetal
 */

#include "mbed.h"

DigitalOut  	led1(PC_7);
DigitalOut  	led2(PB_13);
DigitalOut		ledN(PA_5);

InterruptIn		sw1(PA_11);
InterruptIn		sw2(PA_12);
InterruptIn		userB(PC_13);


void sw1Int(void){
	led1 = !led1;
}


void sw2Int(void){
	led2 = !led2;
}


int main()
{
		printf("Hello L476RG - LEnsE !!\r\n");
	
		led1 = 1;
		led2 = 1;
	
		sw1.rise(&sw1Int);
		sw2.rise(&sw2Int);

    while(1)
    {
				ledN = userB.read();
				thread_sleep_for(100);
    }
}