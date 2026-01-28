/**
 * FILENAME :        sh1107_constants.h          
 *
 * DESCRIPTION :
 *       LCD M5Stack SH1107 1.3" LCD display - Library
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    26/jan/2026
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */
 
#ifndef __SSD1306_CONSTANTS_H__
#define __SSD1306_CONSTANTS_H__

  // Success / Error
  // -----------------------------------
  #define SH1107_SUCCESS        true
  #define SH1107_ERROR          false

#define 	SSD_I2C_FREQ		100000

#define     SH_I2C_ADDRESS     0x3C
#define		SH_I2C_CMD		0x00
#define		SH_I2C_DATA		0x40


  // Colors
  // -----------------------------------
  #define SH1107_BLACK         0
  #define SH1107_WHITE         1

  // AREA definition
  // -----------------------------------
  #define MAX_X                 128               // max columns / MV = 0 in MADCTL
  #define MAX_Y                 64                // max rows / MV = 0 in MADCTL
  #define SIZE_X                MAX_X - 1         // columns max counter
  #define SIZE_Y                MAX_Y - 1         // rows max counter
  #define CACHE_SIZE_MEM        (MAX_X * MAX_Y)   // whole pixels

#define SH1107_MEMORYMODE 0x20          ///< See datasheet
#define SH1107_COLUMNADDR 0x21          ///< See datasheet
#define SH1107_PAGEADDR 0x22            ///< See datasheet
#define SH1107_SETCONTRAST 0x81         ///< See datasheet
#define SH1107_CHARGEPUMP 0x8D          ///< See datasheet
#define SH1107_SEGREMAP 0xA0            ///< See datasheet
#define SH1107_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SH1107_DISPLAYALLON 0xA5        ///< Not currently used
#define SH1107_NORMALDISPLAY 0xA6       ///< See datasheet
#define SH1107_INVERTDISPLAY 0xA7       ///< See datasheet
#define SH1107_SETMULTIPLEX 0xA8        ///< See datasheet
#define SH1107_DCDC 0xAD                ///< See datasheet
#define SH1107_DISPLAYOFF 0xAE          ///< See datasheet
#define SH1107_DISPLAYON 0xAF           ///< See datasheet
#define SH1107_SETPAGEADDR   0xB0 		  ///< Specify page address to load display RAM data to page address
       ///< register
#define SH1107_COMSCANINC 0xC0         ///< Not currently used
#define SH1107_COMSCANDEC 0xC8         ///< See datasheet
#define SH1107_SETDISPLAYOFFSET 0xD3   ///< See datasheet
#define SH1107_SETDISPLAYCLOCKDIV 0xD5 ///< See datasheet
#define SH1107_SETPRECHARGE 0xD9       ///< See datasheet
#define SH1107_SETCOMPINS 0xDA         ///< See datasheet
#define SH1107_SETVCOMDETECT 0xDB      ///< See datasheet
#define SH1107_SETDISPSTARTLINE      0xDC ///< Specify Column address to determine the initial display line or
       ///< COM0.

#define SH1107_SETLOWCOLUMN 0x00  ///< Not currently used
#define SH1107_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SH1107_SETSTARTLINE 0x40  ///< See datasheet

#endif