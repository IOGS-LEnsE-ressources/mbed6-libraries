/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "ssd1306.h"
#include "ssd1306_constants.h"
#define     K_GAIN  3

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

AnalogIn    t_consigne(PA_1);
AnalogIn    t_mesure(PA_0);

DigitalIn   mode_in(PA_11);

AnalogOut   comp_erreur(PA_4);
AnalogOut   mesure_out(PA_5);
DigitalOut  led_signe(PA_7);

PwmOut      moteur_1(PB_1);  
PwmOut      moteur_2(PB_0);  

Ticker tik;
DigitalOut  cnt_tik(PA_2);

I2C         my_i2c(PB_7, PB_6);
SSD1306     my_lcd(&my_i2c, MAX_X, MAX_Y);

float   t_consigne_f = 0.0;
float   t_mesure_f = 0.0;
float   t_erreur_f = 0.0;


void tik_ISR(void){
    if(mode_in == 1){
        cnt_tik = !cnt_tik;
        t_consigne_f = t_consigne.read() - 0.5;
        t_mesure_f = t_mesure.read() - 0.5;
        t_erreur_f = t_consigne_f - t_mesure_f;

        if(t_erreur_f >= 0){    
            comp_erreur.write(t_erreur_f); 
            led_signe = 0; 
            moteur_1.write(K_GAIN*t_erreur_f);  
            moteur_2.write(0); 
        }
        else{    
            comp_erreur.write(-t_erreur_f); 
            led_signe = 1; 
            moteur_1.write(0);  
            moteur_2.write(K_GAIN*t_erreur_f);   
        }
    }
    else{
        t_consigne_f = t_consigne.read();
        comp_erreur.write(t_consigne_f); 
        moteur_1.write(t_consigne_f);  
        moteur_2.write(t_consigne_f);
    }
    
}

int main()
{
    printf("Test  7 - signe erreur + PWM + OLED  %.1lf\r\n", 0.1);

    moteur_1.period_ms(10);
    moteur_2.period_ms(10);
    moteur_1.write(0);
    moteur_2.write(0);
    my_lcd.init();
	my_lcd.clear_screen();
    thread_sleep_for(200);

    tik.attach(&tik_ISR, 100us);
    led1 = 1;

    my_lcd.draw_pixel(5, 10, SSD1306_WHITE);
    my_lcd.fill_rect(10, 20, 20, 30, SSD1306_WHITE);
    my_lcd.set_position(50, 20);
    my_lcd.draw_string("Test LCD", SSD1306_WHITE, NORMAL);
    
    my_lcd.draw_line(30, 50, 60, 40, SSD1306_WHITE);
    my_lcd.display();

    while (true)
    {
        //cnt_tik = !cnt_tik;
        thread_sleep_for(WAIT_TIME_MS);
    }
}
