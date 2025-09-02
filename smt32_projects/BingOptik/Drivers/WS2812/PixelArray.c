#include "PixelArray.h"


void init_array(PixelArray *pixels, int nb_pixels, int nb_bits){
	pixels->__nb_pixels = nb_pixels;
	pixels->__nb_bits = nb_bits;
	pixels->_array = (int*)malloc(nb_pixels * sizeof(int));
}


void set_all_RGB(PixelArray *pixels, short r, short g, short b){
    for(int i = 0; i < pixels->__nb_pixels; i++){
    	set_pix_RGB(pixels, i, r, g, b);
    }
}

void set_pix_RGB(PixelArray *pixels, int pix, short r, short g, short b){
    int val = 0;
    if(pixels->__nb_bits == WS2812_STD)
        val = (g << 16) + (r << 8) + b;
    if(pixels->__nb_bits == WS2812_WHI)
        val = (g << 24) + (r << 16) + (b << 8);
    pixels->_array[pix] = val;
}

int* get_array(PixelArray *pixels){
    return pixels->_array;
}

void set_black_all(PixelArray *pixels){
	set_all_RGB(pixels, 0, 0, 0);
}
