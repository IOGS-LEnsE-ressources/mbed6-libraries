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

WS2812  my_strip1(PC_0, STRIP_SIZE, WS2812_STD); // Head Light 1
WS2812  my_strip2(PA_10, STRIP_SIZE, WS2812_STD); // Head Light 2
WS2812  my_strip3(PC_5, STRIP_SIZE, WS2812_STD); // Head Light 3
WS2812  my_strip4(PA_13, STRIP_SIZE, WS2812_STD); // Head Light 4
PixelArray my_leds1(STRIP_SIZE, WS2812_STD);
PixelArray my_leds2(STRIP_SIZE, WS2812_STD);
PixelArray my_leds3(STRIP_SIZE, WS2812_STD);
PixelArray my_leds4(STRIP_SIZE, WS2812_STD);

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



// Main function
int main() {
	init_strips();
	int cpt = 0;

	while(1){
		change_strip(1, (cpt%4)*50, 0, 128);
		change_strip(2, 0, (cpt%4)*50, 0);
		change_strip(3, 64, 64, (cpt%4)*50);
		change_strip(4, 64, (cpt%10)*20, );
		update_strips();
		thread_sleep_for(500);
			
		cpt+=1;
	}
}