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

InterruptIn		sw1(PA_11);
InterruptIn		sw2(PA_12);
InterruptIn		userB(PC_13);

PwmOut 				motor_R1(PA_0);
PwmOut 				motor_R2(PA_1);
PwmOut 				motor_L1(PB_4);
PwmOut 				motor_L2(PA_8);
DigitalOut		motor_en(PA_9);


void init_motor(){
	motor_en = 0;
	motor_L1.period_ms(10);
	motor_L1.write(0);
	motor_R1.period_ms(10);
	motor_R1.write(0);
	motor_L2.period_ms(10);
	motor_L2.write(0);
	motor_R2.period_ms(10);
	motor_R2.write(0);
}

void stop(){
	motor_en = 0;
}

void right_motor(float speed, bool direction){
	if(direction){
		motor_R1.write(speed);
		motor_R2.write(0);
	}
	else{
		motor_R1.write(0);
		motor_R2.write(speed);
	}
}
		
void left_motor(float speed, bool direction){
	if(direction){
		motor_L1.write(speed);
		motor_L2.write(0);
	}
	else{
		motor_L1.write(0);
		motor_L2.write(speed);
	}
}	

void sw1Int(void){
	led1 = !led1;
	right_motor(0.7, led1.read());
	motor_en = 1;
}


void sw2Int(void){
	led2 = !led2;
	left_motor(0.7, led2.read());
	motor_en = 1;
}

int main()
{
	init_motor();
	printf("Hello L476RG - LEnsE !!\r\n");
	
	led1 = 1;
	led2 = 1;

	sw1.rise(&sw1Int);
	sw2.rise(&sw2Int);
	userB.fall(&stop);

	while(1)
	{
			thread_sleep_for(100);
	}
}