/*  
 *  Structure of a main file for embedded project @ LEnsE
 *      Switches and LEDs test on Light radiation board
 *
 *  SW1 controls LED1 and SW2 controls LED2 on the board.
 *	https://lense.institutoptique.fr/ressources/Annee1/InterfacageNumerique/bloc_rayonnement/S6_IntNum_TP_Bloc_rayonnement_mbed.pdf
 *****************************************************************
 *  Pinout :
 *      PC_7 - LED1 on the light radiation board
 *      PB_13 - LED2 on the light radiation board
 *      PC_6 - SW1 on the light radiation board
 *      PC_8 - SW2 on the light radiation board
 *****************************************************************
 *  Tested with Nucleo L476RG board / Mbed OS 6
 *****************************************************************
 *  Author : J. VILLEMEJANE / LEnsE - Creation 2025/01/28
 *****************************************************************
 *  LEnsE / https://lense.institutoptique.fr/
 *      Based on Mbed OS 6 example : mbed-os-example-blinky-baremetal
 */

#include "mbed.h"

DigitalOut  led1(PC_7);
DigitalOut  led2(PB_13);
InterruptIn	sw1(PC_6);
InterruptIn	sw2(PC_8);

int main()
{
		printf("Hello L476RG - LEnsE !!\r\n");

    while(1)
    {
				led1 = sw1;
				led2 = sw2;
        thread_sleep_for(40);
    }
}