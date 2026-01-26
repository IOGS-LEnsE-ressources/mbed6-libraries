/**
 * FILENAME :        sh1107.cpp          
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


#include "font.h"
#include "sh1107.h"
#include "sh1107_constants.h"


SH1107::SH1107(I2C *i2c, uint16_t width, uint16_t height){
	this->__width = width;
	this->__height = height;
  /// Set the good size for the data buffer
  this->__buff_size = this->__height * this->__width / 8;
  this->__buffer.resize(this->__buff_size);
	/// Initialization of the SPI interface
	if(i2c){delete this->__i2c;}
	this->__i2c = i2c;
	this->__i2c->frequency(SSD_I2C_FREQ);
	wait_us(1000);
}


/**************************************************************
 *	Initialization
 **************************************************************/

bool	SH1107::init(void){
	bool ack = true;
  ack = ack && this->send_command(SH1107_DISPLAYOFF);
  return ack;
}

bool SH1107::clear_screen(void)
{
    for(int i = 0; i < this->__buff_size; i++){
        this->__buffer[i] = 0;
    }
    return this->display();
}


/**************************************************************
 *	Display On and Off
 **************************************************************/

bool 	SH1107::display_on(void)
{
	bool ack = true;
  ack = ack && this->send_command(SH1107_DISPLAYON);
  return ack;
}

bool 	SH1107::display_off(void)
{
	bool ack = true;
  ack = ack && this->send_command(SH1107_DISPLAYOFF);
  return ack;
}

void    SH1107::invertDisplay(bool i)
{
    //
}

/**************************************************************
 *	Commands and data transmission
 **************************************************************/

bool SH1107::send_command(char cmd){
	int ack;
	char data[2];
	data[0] = 0;
	data[1] = cmd;
	ack = this->__i2c->write(SH_I2C_ADDRESS << 1, data, 2);
  return  (ack == 0) ? SH1107_SUCCESS : SH1107_ERROR;
}

bool 	SH1107::send_data(char* data, uint16_t size)
{
	int ack;
	ack = this->__i2c->write(SH_I2C_ADDRESS << 1, data, size);
  return  (ack == 0) ? SH1107_SUCCESS : SH1107_ERROR;
}

bool    SH1107::display(){
  bool ack = true;
	char data[4];
	data[0] = 0;
	data[1] = SH1107_SETPAGEADDR;
	data[2] = 0x10;
	data[3] = 0;
	
  ack = ack && this->send_data(data, 4);  
	
  return  ack;
}

std::vector<uint8_t> SH1107::get_buffer(void){
    return this->__buffer;
}

/**************************************************************
 *	Windows and position
 **************************************************************/

bool    SH1107::check_range(uint16_t x, uint16_t y)
{
	// check if coordinates is out of range
	if ((x > this->__width)  ||	(x < 0) ||
		(y > this->__height)  ||	(y < 0)){
		// out of range
		return SH1107_ERROR;
	}
	// success
	return SH1107_SUCCESS;
}

bool    SH1107::check_value_range(uint16_t val, uint16_t min, uint16_t max)
{
	// check if coordinates is out of range
	if ((val > max)  ||	(val < min)){	return SH1107_ERROR; }
	// success
	return SH1107_SUCCESS;
}

/**************************************************************
 *	Drawings
 **************************************************************/

bool 	SH1107::draw_pixel (uint16_t x, uint16_t y, uint16_t color)
{
    // check if coordinates is out of range
    if (!this->check_range(x, y)) { return SH1107_ERROR; }

    // x is which column
    if (color == SH1107_WHITE) 
        this->__buffer[x+ (y/8) * this->__width] |= (1 << (y%8));  
    else // else black
        this->__buffer[x+ (y/8) * this->__width] &= (0 << (y%8));

	return SH1107_SUCCESS;
}



