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
	this->clear_buffer();
	/// Initialization of the SPI interface
	if(i2c){delete this->__i2c;}
	this->__i2c = i2c;
	this->__i2c->frequency(SSD_I2C_FREQ);
	wait_us(1000);
}

void SH1107::clear_buffer()
{
    memset(__buffer.data(), 0x00, __buffer.size());
}

/**************************************************************
 *	Initialization
 **************************************************************/

bool	SH1107::init(void){
	uint8_t data[2];
	bool ack = true;
  ack = ack && this->send_command(SH1107_DISPLAYOFF);
	// 
	data[0] = SH1107_SETDISPLAYCLOCKDIV;
	data[1] = 0x50;
  ack = ack && this->send_command_list(data, 2);
	data[0] = SH1107_SETMULTIPLEX;
	data[1] = 0x3F;
  ack = ack && this->send_command_list(data, 2);
	data[0] = SH1107_SETDISPLAYOFFSET;
	data[1] = 0x00;
  ack = ack && this->send_command_list(data, 2);
	ack = ack && this->send_command(SH1107_SETSTARTLINE);
	data[0] = SH1107_DCDC;
	data[1] = 0x8A;
  ack = ack && this->send_command_list(data, 2);
	data[0] = SH1107_MEMORYMODE;
	data[1] = 0x00;
  ack = ack && this->send_command_list(data, 2);
	//ack = ack && this->send_command(0xA1);	// ORIENTATION HORIZONTAL - 0xC8 for VERTICAL
	data[0] = SH1107_SETCOMPINS;
	data[1] = 0x12;
  ack = ack && this->send_command_list(data, 2);
	data[0] = SH1107_SETCONTRAST;
	data[1] = 0x80;
  ack = ack && this->send_command_list(data, 2);
	data[0] = SH1107_SETPRECHARGE;
	data[1] = 0x22;
  ack = ack && this->send_command_list(data, 2);
	data[0] = SH1107_SETVCOMDETECT;
	data[1] = 0x35;
  ack = ack && this->send_command_list(data, 2);
	ack = ack && this->send_command(SH1107_DISPLAYALLON_RESUME);
	ack = ack && this->send_command(SH1107_NORMALDISPLAY);
	ack = ack && this->send_command(SH1107_DISPLAYON);
	
  return ack;
}

bool SH1107::clear_screen(void)
{
    this->clear_buffer();
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

bool SH1107::send_command(uint8_t cmd){
	int ack;
	char data[2];
	data[0] = 0;
	data[1] = cmd;
	ack = this->__i2c->write(SH_I2C_ADDRESS << 1, data, 2);
  return  (ack == 0) ? SH1107_SUCCESS : SH1107_ERROR;
}

bool SH1107::send_command_list(uint8_t* cmds, uint16_t size){
	bool ack = SH1107_SUCCESS;
	ack = ack && this->__i2c->write(SH_I2C_ADDRESS << 1);
	ack = ack && this->__i2c->write(SH_I2C_CMD);
	for (int i = 0; i < size; i++){
		ack = ack && this->__i2c->write(cmds[i]);
	}
  return ack;
}

bool 	SH1107::send_data(uint8_t* data, uint16_t size)
{
	bool ack = SH1107_SUCCESS;
	ack = ack && this->__i2c->write(SH_I2C_ADDRESS << 1);
	ack = ack && this->__i2c->write(SH_I2C_DATA);
	for (int i = 0; i < size; i++){
		ack = ack && this->__i2c->write(data[i]);
	}
  return ack;
}

bool    SH1107::display(){
  bool ack = true;
	uint8_t pages = this->	__height / 8;
	for (uint8_t page = 0; page < pages; page++)
	{
			ack = ack && this->send_command(0xB0 + page);  // Page
			ack = ack && this->send_command(SH1107_SETHIGHCOLUMN); 	 // High column        
			ack = ack && this->send_command(SH1107_SETLOWCOLUMN);    // Low column

			// Transfer 128 bytes per page
			ack = ack && this->send_data(this->__buffer.data() + page * this->__width, this->__width);
	}
	
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
	return (x < __width) && (y < __height);
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

bool SH1107::draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if (!check_range(x, y)) return SH1107_ERROR;

    uint16_t index = x + (y / 8) * __width;
    uint8_t  mask  = 1 << (y % 8);

    if (color == SH1107_WHITE)
        __buffer[index] |= mask;
    else
        __buffer[index] &= ~mask;

    return SH1107_SUCCESS;
}



