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
	
	
	// Contrast
	data[0] = 0x00; data[1] = 0x81; data[2] = 0x50;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
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
	
	data[0] = 0x00; data[1] = 0xB5; data[2] = 0x10; data[3] = 0x10;
	ret_value = my_i2c.write(OLED_ADDR << 1, data, 3);
	buffer[0] = 0x40;
	ret_value = my_i2c.write(OLED_ADDR << 1, (char *)buffer, 129);
	printf("R-Cmd = %d \n", ret_value);

	
	
	while (1) {
		// boucle vide, écran reste affiché
		thread_sleep_for(100);
	}
}

