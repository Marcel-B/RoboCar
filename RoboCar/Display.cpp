#include "Display.h"

void init(int display)
{
	wiringPiI2CWriteReg8(display, 0x00, 0xae); // display off
	wiringPiI2CWriteReg8(display, 0x00, 0xd5); // clockdiv
	wiringPiI2CWriteReg8(display, 0x00, 0x80);
	wiringPiI2CWriteReg8(display, 0x00, 0xa8); // multiplex
	wiringPiI2CWriteReg8(display, 0x00, 0x3f);
	wiringPiI2CWriteReg8(display, 0x00, 0xd3); // offset
	wiringPiI2CWriteReg8(display, 0x00, 0x00);
	wiringPiI2CWriteReg8(display, 0x00, 0x40); // startline
	wiringPiI2CWriteReg8(display, 0x00, 0x8d); // charge pump
	wiringPiI2CWriteReg8(display, 0x00, 0x14);
	wiringPiI2CWriteReg8(display, 0x00, 0x20); // memory mode
	wiringPiI2CWriteReg8(display, 0x00, 0x00);
	//wiringPiI2CWriteReg8(display,0x00,0x01);
	wiringPiI2CWriteReg8(display, 0x00, 0xa1); // segregmap
	wiringPiI2CWriteReg8(display, 0x00, 0xc8); // comscandec
	wiringPiI2CWriteReg8(display, 0x00, 0xda); // set com pins
	wiringPiI2CWriteReg8(display, 0x00, 0x12);
	wiringPiI2CWriteReg8(display, 0x00, 0x81); // contrast
	wiringPiI2CWriteReg8(display, 0x00, 0xcf);
	wiringPiI2CWriteReg8(display, 0x00, 0xd9); // precharge
	wiringPiI2CWriteReg8(display, 0x00, 0xf1);
	wiringPiI2CWriteReg8(display, 0x00, 0xdb); // vcom detect
	wiringPiI2CWriteReg8(display, 0x00, 0x40);
	wiringPiI2CWriteReg8(display, 0x00, 0xa4); // resume
	wiringPiI2CWriteReg8(display, 0x00, 0xa6); // normal (not inverted)
	wiringPiI2CWriteReg8(display, 0x00, 0xaf); // display on
}
void render(int display, char *bitmap) {
	char m[8], n[8] = { 0 };
	memcpy(&m, bitmap, 8);
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			//choose one:
			n[y] |= (m[x] & (1 << (7 - y))) >> (7 - y) << x; // 270 grad drehen
		}
	}
	for (int x = 7; x >= 0; x--) {
		int a = (int)n[x];
		wiringPiI2CWriteReg8(display, 0x40, a);
	}
}
void reset_pos(int display)
{
	wiringPiI2CWriteReg8(display, 0x00, 0xb0);
	wiringPiI2CWriteReg8(display, 0x00, 0x00);
	wiringPiI2CWriteReg8(display, 0x00, 0x10);
}
void clear(int display)
{
	reset_pos(display);
	for (int x = 0; x < 128; x++) {
		for (int y = 0; y < 8; y++) {
			wiringPiI2CWriteReg8(display, 0x40, 0x00);
		}
	}
}
void clear2(int display)
{
	reset_pos(display);
	for (int x = 0; x < 128; x++) {
		for (int y = 0; y < 8; y++) {
			wiringPiI2CWriteReg8(display, 0x40, 0xff);
		}
	}
}
char house[8] =
{
	0b00011000,
	0b00111100,
	0b01111110,
	0b11111111,
	0b01100110,
	0b01100110,
	0b01100110,
	0b00000000,
};

char _A[8] =
{
	0x0,
	0x18,
	0x24,
	0x24,
	0x3C,
	0x24,
	0x24,
	0x0,
};

int start_up(int handle)
{
	init(handle);
	clear(handle);
	render(handle, _A);
}

