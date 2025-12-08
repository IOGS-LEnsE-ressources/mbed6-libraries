/*  
 *  Structure of a main file for embedded project @ LEnsE
 *      Test code for WS2812 controlling
 *
 *  This code allows to blink WS2812 LED in different colors. 
 *****************************************************************
 *  Pinout :
 *		PC_0 - Output to Led Strip input (2 pixels)
 *****************************************************************
 *  Tested with Nucleo L476RG board / Mbed OS 6.17
 *****************************************************************
 *  Author : J. VILLEMEJANE / LEnsE - Creation 2025/02/12
 *****************************************************************
 *  LEnsE / https://lense.institutoptique.fr/
 *      Based on Mbed OS 6 example : mbed-os-example-blinky-baremetal
 */

#include "mbed.h"
#include "WS2812.h"
#include "PixelArray.h"

#define     STRIP_SIZE      2

// Inputs / Outputs
DigitalOut  	led1(PC_7);
DigitalOut  	led2(PB_13);

InterruptIn		sw1(PA_11);
InterruptIn		sw2(PA_12);
InterruptIn		userB(PC_13);

// HeadLights
WS2812  my_strip1(PC_0, STRIP_SIZE, WS2812_STD); // Head Light 1
WS2812  my_strip2(PA_10, STRIP_SIZE, WS2812_STD); // Head Light 2
WS2812  my_strip3(PC_5, STRIP_SIZE, WS2812_STD); // Head Light 3
WS2812  my_strip4(PA_13, STRIP_SIZE, WS2812_STD); // Head Light 4
PixelArray my_leds1(STRIP_SIZE, WS2812_STD);
PixelArray my_leds2(STRIP_SIZE, WS2812_STD);
PixelArray my_leds3(STRIP_SIZE, WS2812_STD);
PixelArray my_leds4(STRIP_SIZE, WS2812_STD);

// Motors
PwmOut 				motor_R1(PA_0);
PwmOut 				motor_R2(PA_1);
PwmOut 				motor_L1(PB_4);
PwmOut 				motor_L2(PA_8);
DigitalOut		motor_en(PA_9);

void init_strips(){
	my_strip1.set_timings(6, 13, 14, 5);
	my_strip2.set_timings(6, 13, 14, 5);
	my_strip3.set_timings(6, 13, 14, 5);
	my_strip4.set_timings(6, 13, 14, 5);

	my_strip1.break_trame();
	my_strip1.send_leds(my_leds1.get_array()); 
	my_strip2.break_trame();
	my_strip2.send_leds(my_leds2.get_array()); 
	my_strip3.break_trame();
	my_strip3.send_leds(my_leds3.get_array()); 
	my_strip4.break_trame();
	my_strip4.send_leds(my_leds4.get_array()); 
}

void update_strips(){	
	my_strip1.break_trame();
	my_strip2.break_trame();
	my_strip3.break_trame();
	my_strip4.break_trame();
	wait_us(200000);
	my_strip1.send_leds(my_leds1.get_array());
	my_strip2.send_leds(my_leds2.get_array());
	my_strip3.send_leds(my_leds3.get_array());
	my_strip4.send_leds(my_leds4.get_array());
}

void change_strip(short nb, short r, short g, short b){
	switch(nb){
		case 1:
			my_leds1.set_all_RGB(r, g, b);
			break;
		case 2:
			my_leds2.set_all_RGB(r, g, b);
			break;
		case 3:
			my_leds3.set_all_RGB(r, g, b);
			break;
		case 4:
			my_leds4.set_all_RGB(r, g, b);
			break;
		default:
			my_leds1.set_all_RGB(r, g, b);
	}
}

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

// Main function
int main() {
	init_strips();
	init_motor();
	int cpt = 0;

	printf("JoyIt car - LEnsE !!\r\n");
	
	led1 = 1;
	led2 = 1;

	sw1.rise(&sw1Int);
	sw2.rise(&sw2Int);
	userB.fall(&stop);
	
	
	while(1){
		change_strip(1, (cpt%4)*50, 0, 128);
		change_strip(2, 0, (cpt%4)*50, 0);
		change_strip(3, 64, 64, (cpt%4)*50);
		change_strip(4, 64, (cpt%10)*20, 0);
		update_strips();
		thread_sleep_for(500);
			
		cpt+=1;
	}
}