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

WS2812  my_strip(PC_0, STRIP_SIZE, WS2812_STD);
PixelArray my_leds(STRIP_SIZE, WS2812_STD);
int colors[STRIP_SIZE];

// Main function
int main() {
    my_strip.set_timings(6, 13, 14, 5);

    my_strip.break_trame();
    my_strip.send_leds(my_leds.get_array()); 

    int cpt = 0;

    while(1){
        my_strip.break_trame();
        wait_us(200000);
        my_leds.set_all_RGB(255, 0, 128);
        my_strip.send_leds(my_leds.get_array());

        my_strip.break_trame();
        wait_us(200000);  
        my_leds.set_black_all();
        my_strip.send_leds(my_leds.get_array());

        my_strip.break_trame();
        wait_us(200000);  
        my_leds.set_pix_RGB(cpt%STRIP_SIZE, 0, 255, 0);
        my_strip.send_leds(my_leds.get_array());

        my_strip.break_trame();
        wait_us(200000);  
        my_leds.set_black_all();
        my_strip.send_leds(my_leds.get_array());
        
        cpt+=1;
    }
}