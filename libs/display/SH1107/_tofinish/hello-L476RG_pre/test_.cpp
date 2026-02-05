#include "mbed.h"

// === Pins I2C ===
I2C my_i2c(I2C_SDA, I2C_SCL);
const int OLED_ADDR = 0x3C;  // adresse I2C
const int I2C_FREQ = 400000;

char data[10];

uint8_t buffer[129] = {0xAA};

// === Exemple Main ===
int main() {
	int ret_value = 0;	
	printf("NEW TEST\n"	);

	my_i2c.frequency(I2C_FREQ);
	thread_sleep_for(200);
	// Display Off
	data[0] = 0x00; data[1] = 0xAE;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-Off = %d \n", ret_value);
	thread_sleep_for(100);
	// Set Clock
	data[0] = 0x00; data[1] = 0xD5; data[2] = 0x50;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-Ck = %d \n", ret_value);
	// Multiplex 64
	data[0] = 0x00; data[1] = 0xA8; data[2] = 0x3F;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-64 = %d \n", ret_value);
	// Display offset
	data[0] = 0x00; data[1] = 0xD3; data[2] = 0x00;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-Offs = %d \n", ret_value);
	// Start Line
	data[0] = 0x00; data[1] = 0x40;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-St = %d \n", ret_value);
	// Internal DC/DC
	data[0] = 0x00; data[1] = 0xAD; data[2] = 0x00;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-DC = %d \n", ret_value);	
	// Page addressing mode
	data[0] = 0x00; data[1] = 0x20; data[2] = 0x00;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-Page = %d \n", ret_value);
	// Segment remap
	data[0] = 0x00; data[1] = 0xA1;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-Remap = %d \n", ret_value);
		// COM scan
	data[0] = 0x00; data[1] = 0xC8; 
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-Cont = %d \n", ret_value);
	// COM pins
	data[0] = 0x00; data[1] = 0xDA; data[2] = 0x12; 
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-Cont = %d \n", ret_value);
	// Contrast
	data[0] = 0x00; data[1] = 0x81; data[2] = 0x80;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-Cont = %d \n", ret_value);
	// Precharge
	data[0] = 0x00; data[1] = 0xD9; data[2] = 0x22;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-Cont = %d \n", ret_value);
	// VCOMH
	data[0] = 0x00; data[1] = 0xDB; data[2] = 0x35;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	printf("R-Cont = %d \n", ret_value);
	// Resume RAM display
	data[0] = 0x00; data[1] = 0xA4;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-Cont = %d \n", ret_value);	
	// Normal Display
	data[0] = 0x00; data[1] = 0xA6;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-Nor = %d \n", ret_value);	
	// Display On
	data[0] = 0x00; data[1] = 0xAE;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 2);
	printf("R-On = %d \n", ret_value);
	
	// Update Screen
	for(int page = 0; page < 8; page++){
		data[0] = 0x00; data[1] = 0xB0 + page; data[2] = 0x10; data[3] = 0x00;
		ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
		printf("R-Cmd = %d \n", ret_value);
		buffer[0] = 0x40;
		ret_value = my_i2c.write(OLED_ADDR << 1, (char *)buffer, 65);
		printf("R-Cmd = %d \n", ret_value);
	}

	
	
	while (1) {
		// boucle vide, écran reste affiché
		thread_sleep_for(100);
	}
}

