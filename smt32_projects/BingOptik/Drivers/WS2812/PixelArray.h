/**
 * FILENAME :        PixelArray.h          
 *
 * DESCRIPTION :
 *       Pixel Array class definition / Especially for LEDs Strips
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    25/oct/2023
 *
 *       LEnsE / Institut d'Optique Graduate School
 */

#ifndef     __PIXEL_ARRAY_H_HEADER_H__
#define     __PIXEL_ARRAY_H_HEADER_H__

#include 	<stdlib.h>


#define     WS2812_STD      24
#define     WS2812_WHI      32


typedef struct{
    int *_array;
    int __nb_pixels;
    int __nb_bits;

} PixelArray;

/**
*/
void init_array(PixelArray *pixels, int nb_pixels, int nb_bits);
/**
*/
void set_all_RGB(PixelArray *pixels, short r, short g, short b);
/**
*/
void set_pix_RGB(PixelArray *pixels, int pix, short r, short g, short b);
/**
*/
int* get_array(PixelArray *pixels);
/**
*/
void set_black_all(PixelArray *pixels);

#endif
