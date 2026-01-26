/**
 * FILENAME :        main_sh1107.cpp          
 *
 * DESCRIPTION :
 *       LCD M5Stack SH1107 1.3" LCD display - Library - Testing program
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    26/jan/2026
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 
 https://shop.m5stack.com/products/oled-unit-1-3-128-64-display?srsltid=AfmBOopJFLvQH6R0dFlrS25it2QRkrFLRceAjWcS_ZJdHmux4IfYOJxJ&variant=39813420155052
 */


#include "mbed.h"
#include "sh1107.h"

/// Inputs/outputs declaration 
Ticker controlLoopTik;


I2C         my_i2c(PB_9, PB_8);
SH1107	    my_lcd(&my_i2c, MAX_X, MAX_Y);


/* Methods */
/**
 * Interrupt routine attached to the sampling of the Contol Loop System
 *
 * @return Updates the system control loop outputs
 */
void ISR_controlLoopTik(void);

/**
 * Interrupt routine attached to the mode change button
 */
void ISR_change_mode(void);


// 
int	cpt = 0;

/* Main code */
int main()
{
  // Initialization 
  printf("OLED M5 SH1107 / LCD Screen / Initialization\r\n");
	bool ack = my_lcd.init();
	printf("\t\tInit OK ? %d \r\n", ack); 
	//ack = my_lcd.clear_screen();
	printf("\t\tClear OK ? %d \r\n", ack); 
  printf("\tEND Initialization\r\n");
	
	thread_sleep_for(100);
	ack = my_lcd.display_on();
	printf("\t\tOn OK ? %d \r\n", ack); 
  
	/*
  my_lcd.set_position(10, 50);
  my_lcd.draw_char('a', ST7735_BLUE, NORMAL);
  my_lcd.set_position(80, 100);
	my_lcd.draw_char('V', ST7735_GREEN, NORMAL);

    if(my_lcd.set_position(10, 10)){
        my_lcd.draw_string("Test LCD", ST7735_GREEN, NORMAL);
    }
    
    my_lcd.draw_line(30, 50, 100, 40, ST7735_DONT_KNOW);
    my_lcd.draw_line(30, 50, 20, 60, ST7735_BLUE);

    my_lcd.draw_rect(50, 50, 20, 30, ST7735_GREEN);
    my_lcd.fill_rect(55, 55, 10, 20, ST7735_BLUE);

    // Initialization of interrupt on falling edge of the push button
    mode_change.fall(&ISR_change_mode);

    // Initialization of main ticker
    controlLoopTik.attach(&ISR_controlLoopTik, 100ms);
    */
    while (true){
        /*
		if(cpt % 20 == 0){
            // BackLight can not be disable on the Joy-IT RB-TFT1.8
			my_lcd.display_off();
		}
		if(cpt % 20 == 10){
			my_lcd.display_on();
		}
		*/
			thread_sleep_for(100);
    }
}


/* */
void ISR_controlLoopTik(void){
    //printf("Main\r\n");
	cpt++;
}

/* */
void ISR_change_mode(void){
    printf("Button\r\n");
}
