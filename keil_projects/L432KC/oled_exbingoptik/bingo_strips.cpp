#include "bingo_strips.h"

enum 		Mode 		mode = BINGO;

WS2812  strip_mirror(PA_6, STRIP_SIZE_MIRROR, WS2812_STD);
PixelArray leds_mirror(STRIP_SIZE_MIRROR, WS2812_STD);

WS2812  strip_bobine(PA_4, STRIP_SIZE_BOBINE, WS2812_STD);
PixelArray leds_bobine(STRIP_SIZE_BOBINE, WS2812_STD);

DigitalOut led1(LED1);
DigitalOut sync_screen(PB_5);

InterruptIn	mvt_detect_in(PA_7);
int					mvt_cnt = 0;
int					mvt_cnt_old = 0;
bool				mvt_detected = false;
int					mvt_speed_cnt = 0;
int					mvt_speed_cnt_old = 0;


DigitalIn   mode_in(PA_11);
Ticker tik;
Ticker tik_smooth;
DigitalOut  cnt_tik(PA_2);

int					tik_cnt = 0;
int					tik_cnt_smooth = 0;

/* BINGO MODE - Mirror strip*/
void bingo_mirror(void){
	strip_mirror.break_trame();
	if(mvt_speed_cnt_old < SPEED_MAX){  // Fast
		for(int k = 0; k < STRIP_SIZE_MIRROR; k++){
			uint8_t val = sine_table[(k+2*mvt_cnt)%110];
			int led_nb = mvt_cnt % COLOR_VARIATION;
			leds_mirror.set_pix_RGB(k, val*R_trans[led_nb], val*G_trans[led_nb], val*B_trans[led_nb]);
		}
		mvt_cnt_old = mvt_cnt;
	}
	else{
		for(int k = 0; k < STRIP_SIZE_MIRROR; k++){
			uint8_t val = sine_table[(k+mvt_cnt_old)%110];
			int led_nb = mvt_cnt_old % 6;
			leds_mirror.set_pix_RGB(k, val*R_val[led_nb], val*G_val[led_nb], val*B_val[led_nb]);
		}
	}
	strip_mirror.send_leds(leds_mirror.get_array());
	
	// Sync
	if(mvt_cnt % COLOR_VARIATION == 0){
		sync_screen = 1;
	}
	else{
		sync_screen = 0;
	}
}


/* SMOOTH MODE - Mirror strip*/
void smooth_mirror(void){
	strip_mirror.break_trame();
	for(int k = 0; k < STRIP_SIZE_MIRROR; k++){
		uint8_t val = 20; //sine_table[(k)%STRIP_SIZE_MIRROR] / 4;
		int led_nb = (tik_cnt_smooth) % COLOR_VARIATION_S;
		leds_mirror.set_pix_RGB(k, val*R_trans_s[led_nb], val*G_trans_s[led_nb], val*B_trans_s[led_nb]);
	}
	mvt_cnt_old = mvt_cnt;

	strip_mirror.send_leds(leds_mirror.get_array());
	
	// Sync
	if(mvt_cnt % COLOR_VARIATION == 0){
		sync_screen = 1;
	}
	else{
		sync_screen = 0;
	}
}
