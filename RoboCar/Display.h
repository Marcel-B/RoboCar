#ifndef DISPLAY_H
#define DISPLAY_H

#include  "RoboStart.h"
#include <string.h>
#include "Font_Basic.h"

class Display
{

public:

	Display() :
		i2c_handle(-1)
	{
		i2c_handle = wiringPiI2CSetup(0x3c);
		init();
	};

	Display(int handle) :
		i2c_handle(handle)
	{
		init();
	};

	void set_row(const char* row, int length);
	void init() const;
	void start_up();
	void clear();
	void reset_pos();


private:
	int i2c_handle;
	void clear(int handle);
	void clear2(int handle);
	void reset_pos(int display);
};

#endif
