/**
 * FILENAME :        WS2812.h          
 *
 * DESCRIPTION :
 *       WS2812 LEDs Strip controller for STM32 (Nucleo Board)
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    24/oct/2023
 *
 *       LEnsE / Institut d'Optique Graduate School
 */

#ifndef     __WS2812_H_HEADER_H__
#define     __WS2812_H_HEADER_H__
#include "main.h"
#include <stdint.h>

/* Timing Values */
/* For L476RG :
    T0H = 6, T0L = 13, T1H = 14, T1L = 5
    */

/* BUG : t0h not working... */

/* WS2812B */
/*  T0H = 0.4us / T0L = 0.85us
    T1H = 0.8us / T1L = 0.45us
*/

typedef struct{
    /* LED Strip output */
	uint16_t		pin_nb;
	GPIO_TypeDef*	port_name;
    /* Number of LEDs on the strip */
    int         __nb_leds;
    /* Number of bits per LEDs - 24 or 32 */
    int         __nb_bits;
    /* Timing for high and low level values */
    int t0h;
    int t0l;
    int t1h;
    int t1l;
} WS2812;


/**
* @brief Init of a WS2812 LED strip.
* @details Create a WS2812 LEDs Strip controller
* @param pin_strip Output pin to control the LEDs strip
* @param nb_leds Number of LEDs of the strip
* @param nb_bits Number of bits per LEDs - 24 or 32
*/
void init_ws2812(WS2812 *ws, GPIO_TypeDef* port_name, uint16_t pin_strip, int nb_leds, int nb_bits);

/* Setup the timings values */
void set_timings(WS2812 *ws, int t0h, int t0l, int t1h, int t1l);
/* Bit of value equal to 1 */
void send_led_one(WS2812 *ws, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/* Bit of value equal to 0 */
void send_led_zero(WS2812 *ws, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/* Break function between two trames */
void break_trame(WS2812 *ws);
/* Send trame to a led */
void send_led_trame(WS2812 *ws, int cl);
/* Send a complete trame to nb LEDs on a single strips */
void send_leds(WS2812 *ws, int *leds);

/* Blackout */
void blackout(WS2812 *ws);

#endif
