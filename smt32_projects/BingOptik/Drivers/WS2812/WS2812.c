#include "WS2812.h"
#include "main.h"

/* WS2812B */
/*  T0H = 0.4us / T0L = 0.85us
    T1H = 0.8us / T1L = 0.45us
*/

void init_ws2812(WS2812 *ws, GPIO_TypeDef* port_name, uint16_t pin_strip, int nb_leds, int nb_bits)
{
	ws->pin_nb = pin_strip;
	ws->port_name = port_name;
	ws->__nb_leds = nb_leds;
	ws->__nb_bits = nb_bits;
	ws->t0h = 0;
	ws->t0l = 0;
	ws->t1h = 0;
	ws->t1l = 0;
}

void send_led_one(WS2812 *ws, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    int k;
    GPIOx->BSRR = (uint32_t)GPIO_Pin;	// Pin to 1
    for (k = 0; k < ws->t1h; k++)
        __NOP();
    GPIOx->BSRR = ((uint32_t)GPIO_Pin) << 16;	// Pin to 0
    for (k = 0; k < ws->t1l; k++)
    	__NOP();
}

void send_led_zero(WS2812 *ws, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
    int k;
    GPIOx->BSRR = (uint32_t)GPIO_Pin;	// Pin to 1
    for (k = 0; k < ws->t0h; k++)
        __NOP();
    GPIOx->BSRR = ((uint32_t)GPIO_Pin) << 16;	// Pin to 0
    for (k = 0; k < ws->t0l; k++)
    	__NOP();
}

// Break function
void break_trame(WS2812 *ws){
    HAL_GPIO_WritePin(ws->port_name, ws->pin_nb, GPIO_PIN_RESET);
    for(int wk = 0; wk < 100000; wk++){		// To test for 100us ??
    	__NOP();
    }
}

void send_led_trame(WS2812 *ws, int cl){
	uint32_t mask = 1U << (ws->__nb_bits - 1);  // bit le plus significatif
	for (int k = 0; k < ws->__nb_bits; k++) {
	    if (cl & mask) {
	        send_led_one(ws, ws->port_name, ws->pin_nb);
	    } else {
	        send_led_zero(ws, ws->port_name, ws->pin_nb);
	    }
	    mask >>= 1;  // décale le masque à droite
	}
	/*
    for(int k = 0; k < ws->__nb_bits; k++){
        int bin = cl >> (ws->__nb_bits-1-k);
        if((bin & 0x1) == 1){
            send_led_one(ws);
        }else{
            send_led_zero(ws);
        }
    }
    */
}

void send_leds(WS2812 *ws, int *leds){
    __disable_irq();
    if(ws->__nb_bits == 32){
        
    }
    for(int k = 0; k < ws->__nb_leds; k++){
        send_led_trame(ws, leds[k]);
    }
    __enable_irq();
}

void set_timings(WS2812 *ws, int t0h, int t0l, int t1h, int t1l){
    ws->t0h = t0h;
    ws->t0l = t0l;
    ws->t1h = t1h;
    ws->t1l = t1l;
}


void blackout(WS2812 *ws){
    for(int k = 0; k < ws->__nb_leds; k++){
        send_led_trame(ws, 0);
    }
}
