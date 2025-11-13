/*  
 *  Structure of a main file for embedded project @ LEnsE
 *      Servomotor test on Light radiation board
 *
 *  SW1 and SW2 control the angle of the servomotor of the board.
 *	https://lense.institutoptique.fr/ressources/Annee1/InterfacageNumerique/bloc_rayonnement/S6_IntNum_TP_Bloc_rayonnement_mbed.pdf
 *****************************************************************
 *  Pinout :
 *      PC_7 - LED1 on the light radiation board
 *      PB_13 - LED2 on the light radiation board
 *      PC_6 - SW1 on the light radiation board
 *      PC_8 - SW2 on the light radiation board
 *			PB_7 - Servomotor input - 20ms square with duty cycle
 *****************************************************************
 *  Tested with Nucleo L476RG board / Mbed OS 6
 *****************************************************************
 *  Author : J. VILLEMEJANE / LEnsE - Creation 2025/01/28
 *****************************************************************
 *  LEnsE / https://lense.institutoptique.fr/
 *      Based on Mbed OS 6 example : mbed-os-example-blinky-baremetal
 */

#include "mbed.h"
#define		MAX_SERVO 2000
#define		MIN_SERVO	900
#define		MAX_ANGLE 180
#define		MIN_ANGLE	0
#define		RATIO 		1.0*(MAX_SERVO - MIN_SERVO) / (MAX_ANGLE - MIN_ANGLE)

DigitalOut  led1(PC_7);
DigitalOut  led2(PB_13);
InterruptIn	sw1(PC_6);
InterruptIn	sw2(PC_8);
PwmOut			servo(PB_7);

/* Variables */
int min_angle = 0;
int max_angle = 180;
int angle;
int step_angle = 5;

/* Methods */
void inc_angle();
void dec_angle();
void update_servo(int angle);
void inc_ISR();
void dec_ISR();
	

/* ** MAIN FUNCTION ** */
int main()
{
	printf("Hello L476RG - LEnsE !!\r\n");
	servo.period(0.02);
	servo.pulsewidth_us(1500);
	angle = 90;
	
	sw1.rise(&inc_ISR);
	sw2.rise(&dec_ISR);
	
	while(1)
	{
			thread_sleep_for(40);
	}
}

void update_servo(int angle){
	int delta_us = MIN_SERVO + (angle - MIN_ANGLE) * RATIO;
	printf("New Delta = %d (%d) \r\n", delta_us, (int)(RATIO*100));
	servo.pulsewidth_us(delta_us);
}

void inc_angle(){
	angle = angle + step_angle;
	if(angle > max_angle){
		angle = max_angle;
	}
}

void dec_angle(){
	angle = angle - step_angle;
	if(angle < min_angle){
		angle = min_angle;
	}
}

void inc_ISR(){
	led1 = !led1;
	inc_angle();
	update_servo(angle);
}

void dec_ISR(){
	led2 = !led2;
	dec_angle();
	update_servo(angle);
}
