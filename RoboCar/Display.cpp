#include "Display.h"

void Display::init() const
{
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xae); // i2c_handle off
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xd5); // clockdiv
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x80);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xa8); // multiplex
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x3f);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xd3); // offset
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x00);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x40); // startline
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x8d); // charge pump
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x14);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x20); // memory mode
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x00);
	//wiringPiI2CWriteReg8(i2c_handle,0x00,0x01);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xa1); // segregmap
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xc8); // comscandec
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xda); // set com pins
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x12);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x81); // contrast
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xcf);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xd9); // precharge
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xf1);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xdb); // vcom detect
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0x40);
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xa4); // resume
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xa6); // normal (not inverted)
	wiringPiI2CWriteReg8(i2c_handle, 0x00, 0xaf); // i2c_handle on
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
void Display::reset_pos(int display)
{
	wiringPiI2CWriteReg8(display, 0x00, 0xb0);
	wiringPiI2CWriteReg8(display, 0x00, 0x00);
	wiringPiI2CWriteReg8(display, 0x00, 0x10);
}
void Display::reset_pos()
{
	reset_pos(i2c_handle);
}
void Display::clear(int display)
{
	reset_pos(display);
	for (int x = 0; x < 128; x++) {
		for (int y = 0; y < 8; y++) {
			wiringPiI2CWriteReg8(display, 0x40, 0x00);
		}
	}
}
void Display::clear2(int display)
{
	reset_pos(display);
	for (int x = 0; x < 128; x++) {
		for (int y = 0; y < 8; y++) {
			wiringPiI2CWriteReg8(display, 0x40, 0xff);
		}
	}
}
void Display::clear()
{
	clear(i2c_handle);
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


void Display::set_row(const char* row, int length)
{
	clear(i2c_handle);
	int i = 0;
	while (i < length)
	{
		render(i2c_handle, font8x8_basic[(int)row[i++]]);// 1
	}
	if (i < 16)
	{
		while (i < 16)
		{
			render(i2c_handle, font8x8_basic[(int)' ']);// 1
			i++;
		}
	}
	render(i2c_handle, font8x8_basic[(int)'N']);// 1
}

void Display::start_up()
{
	//init(i2c_handle);
	//clear(handle);
	//render(handle, font8x8_basic[(int)'@']);// 1
	//render(handle, font8x8_basic[(int)'M']);// 2
	//render(handle, font8x8_basic[(int)'a']);// 3
	//render(handle, font8x8_basic[(int)'r']);// 4
	//render(handle, font8x8_basic[(int)'c']);// 5
	//render(handle, font8x8_basic[(int)'e']);// 6
	//render(handle, font8x8_basic[(int)'l']);// 7
	//render(handle, font8x8_basic[(int)' ']);// 8
	//render(handle, font8x8_basic[(int)'B']);// 9
	//render(handle, font8x8_basic[(int)'e']);//10
	//render(handle, font8x8_basic[(int)'n']);//11
	//render(handle, font8x8_basic[(int)'d']);//12
	//render(handle, font8x8_basic[(int)'e']);//13
	//render(handle, font8x8_basic[(int)'r']);//14
	//render(handle, font8x8_basic[(int)'s']);//15
	//render(handle, font8x8_basic[(int)'s']);//16

	//render(handle, font8x8_basic[(int)'s']);//c
	//render(handle, font8x8_basic[(int)'s']);//c
	//render(handle, font8x8_basic[(int)'s']);//c
}

