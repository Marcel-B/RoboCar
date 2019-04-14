#ifndef _PCA9685_H 
#define _PCA9685_H 

#include <inttypes.h>
#include <sys/stat.h> 
#include <sys/ioctl.h> 
#include <unistd.h> 
#include <linux/i2c-dev.h> 
#include <stdio.h> /* Standard I/O functions */ 
#include <fcntl.h> 
#include <syslog.h>/* Syslog functionallity */ 
#include <inttypes.h> 
#include <errno.h> 
#include <math.h> 
#include <stdio.h> 
#include <unistd.h>

#define MODE1 0x00//Mode register 1 include <inttypes.h>
#define MODE2 0x01
#define SUBADR1 0x02
#define SUBADR2 0x03
#define SUBADR3 0x04
#define ALLCALLADR 0x05 
#define LED0 0x6
#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9
#define LED_MULTIPLYER 4
#define ALLLED_ON_L 0xFA 
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD
#define PRE_SCALE 0xFE
#define CLOCK_FREQ 25000000.0
#define BUFFER_SIZE 0x08
//! Main class that exports features for PCA9685 chip 
class PCA9685
{
public:
	PCA9685();
	void init(int, int);
	virtual ~PCA9685();
	void reset(void);
	void setPWMFreq(int);
	void setPWM(uint8_t, int, int);
	void setPWM(uint8_t, int);

private:
	int _i2caddr;
	int _i2cbus;
	char busfile[64];
	uint8_t dataBuffer[BUFFER_SIZE];
	uint8_t read_byte(int, uint8_t);
	void write_byte(int, uint8_t, uint8_t);
	int openfd();
};
#endif
