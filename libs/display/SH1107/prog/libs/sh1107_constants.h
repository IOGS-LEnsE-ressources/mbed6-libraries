/**
 * FILENAME :        st7735_constants.h          
 *
 * DESCRIPTION :
 *       LCD Joy-It OLED-0.96 - 0.96' LCD display - Library
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    29/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */
 
#ifndef __SSD1306_CONSTANTS_H__
#define __SSD1306_CONSTANTS_H__

  // Success / Error
  // -----------------------------------
  #define SSD1306_SUCCESS        true
  #define SSD1306_ERROR          false

#define 	SSD_I2C_FREQ		100000

#define     SSD_I2C_ADDRESS     0x3C


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

#define SH110X_MEMORYMODE 0x20          ///< See datasheet
#define SH110X_COLUMNADDR 0x21          ///< See datasheet
#define SH110X_PAGEADDR 0x22            ///< See datasheet
#define SH110X_SETCONTRAST 0x81         ///< See datasheet
#define SH110X_CHARGEPUMP 0x8D          ///< See datasheet
#define SH110X_SEGREMAP 0xA0            ///< See datasheet
#define SH110X_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SH110X_DISPLAYALLON 0xA5        ///< Not currently used
#define SH110X_NORMALDISPLAY 0xA6       ///< See datasheet
#define SH110X_INVERTDISPLAY 0xA7       ///< See datasheet
#define SH110X_SETMULTIPLEX 0xA8        ///< See datasheet
#define SH110X_DCDC 0xAD                ///< See datasheet
#define SH110X_DISPLAYOFF 0xAE          ///< See datasheet
#define SH110X_DISPLAYON 0xAF           ///< See datasheet
#define SH110X_SETPAGEADDR                                                     \
  0xB0 ///< Specify page address to load display RAM data to page address
       ///< register
#define SH110X_COMSCANINC 0xC0         ///< Not currently used
#define SH110X_COMSCANDEC 0xC8         ///< See datasheet
#define SH110X_SETDISPLAYOFFSET 0xD3   ///< See datasheet
#define SH110X_SETDISPLAYCLOCKDIV 0xD5 ///< See datasheet
#define SH110X_SETPRECHARGE 0xD9       ///< See datasheet
#define SH110X_SETCOMPINS 0xDA         ///< See datasheet
#define SH110X_SETVCOMDETECT 0xDB      ///< See datasheet
#define SH110X_SETDISPSTARTLINE                                                \
  0xDC ///< Specify Column address to determine the initial display line or
       ///< COM0.

#define SH110X_SETLOWCOLUMN 0x00  ///< Not currently used
#define SH110X_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SH110X_SETSTARTLINE 0x40  ///< See datasheet

#endif