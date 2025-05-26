/*  
 *  Structure of a main file for embedded project @ LEnsE
 *****************************************************************
 *  Tested with Nucleo XnnnMM board / Mbed OS 6
 *****************************************************************
 *  Pre-compiler json file at the end of this file
 *****************************************************************
 *  ProTIS / https://lense.institutoptique.fr/
 *      Based on Mbed OS 6 example : mbed-os-example-blinky-baremetal
 */

#include "mbed.h"
 
DigitalOut led_ld2(LED1);

int main()
{
    printf("\tLEnsE - L476RG  v%.1lf\n", 1.1);

    while (true)
    {
        led_ld2 = !led_ld2;
				thread_sleep_for(300);	// 300 ms
    }
}
