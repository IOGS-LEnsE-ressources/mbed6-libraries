#include "mbed.h"

InterruptIn  bp(PB_4);

// === Pins I2C ===
I2C i2c(I2C_SDA, I2C_SCL);
const int OLED_ADDR = 0x3C << 1;  // adresse I2C
const int I2C_FREQ = 400000;

// === Écran ===
#define WIDTH 128     // colonnes visibles
#define HEIGHT 64
#define PAGES (HEIGHT)/8
uint8_t buffer[WIDTH * PAGES];  // framebuffer

// === Commandes I2C ===
bool send_command(uint8_t cmd) {
    char data[2] = {0x00, cmd};
		bool ack = i2c.write(OLED_ADDR, data, 2);
    return ack;
}

void send_data(uint8_t *data_ptr, size_t length) {
    char packet[length + 1];
    packet[0] = 0x40; // données
    memcpy(&packet[1], data_ptr, length);
    i2c.write(OLED_ADDR, packet, length + 1);
}

// === Initialisation minimale SH1107 ===
bool sh1107_init() {
	i2c.frequency(I2C_FREQ);
  thread_sleep_for(200);
	bool ack = true;
	ack = ack && send_command(0xAE);               // Display OFF
	ack = ack && send_command(0xD5); ack = ack && send_command(0x50); // Clock
	ack = ack && send_command(0xA8); ack = ack && send_command(0x3F); // Multiplex 64
	send_command(0xD3); send_command(0x00); // Display offset
	send_command(0x40);               // Start line
	send_command(0xAD); send_command(0x8A); // Internal DC/DC
	send_command(0x20); send_command(0x00); // Page addressing mode
	send_command(0xA1);               // Segment remap
	send_command(0xC8);               // COM scan direction
	send_command(0xDA); send_command(0x12); // COM pins
	send_command(0x81); send_command(0x30); // Contrast
	send_command(0xD9); send_command(0x22); // Precharge
	send_command(0xDB); send_command(0x35); // VCOMH
	send_command(0xA4);               // Resume RAM display
	send_command(0xA6);               // Normal display
	send_command(0xAF);               // Display ON
	thread_sleep_for(100);
	return ack;
}

// === Dessiner un pixel dans le framebuffer ===
void draw_pixel(uint16_t x, uint16_t y, bool color) {
    if (x >= WIDTH || y >= HEIGHT) return;
    uint16_t index = x + (y / 8) * WIDTH;
    uint8_t mask = 1 << (y % 8);

    if (color)
        buffer[index] |= mask;
    else
        buffer[index] &= ~mask;
}

// === Dessiner un rectangle rempli ===
void draw_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, bool color) {
    for (uint16_t y = y0; y <= y1; y++) {
        for (uint16_t x = x0; x <= x1; x++) {
            draw_pixel(x, y, color);
        }
    }
}

// === Mettre à jour l'écran (corrige la “neige”) ===
void update_screen() {
    for (uint8_t page = 0; page < PAGES; page++) {
        send_command(0xB0 | page);      // page
        send_command(0x10);              // colonne haute
        send_command(0x00);              // colonne basse (commencer à 0)
        // Envoyer exactement 128 octets par page
        send_data(&buffer[page * WIDTH], WIDTH);
    }
}

// === Effacer l'écran ===
void clear_screen(bool color = false) {
	for(int k = 0; k < sizeof(buffer); k++) buffer[k] = color ? 0xFF : 0x00;
	update_screen();
}

//
void bp_ISR(void){
	bool ack_ = sh1107_init();
	update_screen();
	printf("Init");
}

// === Exemple Main ===
int main() {
	bp.fall(&bp_ISR);

	// Effacer écran noir
	//clear_screen();
	for(int k = 0; k < 32; k++){
		int start = k*64;
		int end = k*64 + 32;
		for(int i = start; i < end; i++){
			buffer[i] = 0xAA;
		}
		for(int i = start+32; i < end+32; i++){
			buffer[i] = 0x55;
		}
	}
	//update_screen();

	while (1) {
		// boucle vide, écran reste affiché
		thread_sleep_for(100);
	}
}

