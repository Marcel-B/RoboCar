#include "PCA9685.h"
void PCA9685::init(int bus, int address) {
	_i2cbus = bus;
	_i2caddr = address;


	snprintf(busfile, sizeof(busfile), "/dev/i2c-%d", bus);

	reset();
}

PCA9685::PCA9685() {
}

PCA9685::~PCA9685() {
	reset();
}

void PCA9685::reset() {
	int fd = openfd();
	if (fd != -1) {
		write_byte(fd, MODE1, 0x00); //Normal mode 
		write_byte(fd, MODE2, 0x04); //Normal mode 
		close(fd);
	}
}

void PCA9685::setPWMFreq(int freq) {


	int fd = openfd();
	if (fd != -1) {
		uint8_t prescale = (CLOCK_FREQ / 4096 / freq) - 1;

		uint8_t oldmode = read_byte(fd, MODE1);

		uint8_t newmode = (oldmode & 0x7F) | 0x10; //sleep

		write_byte(fd, MODE1, newmode); // go to sleep

		write_byte(fd, PRE_SCALE, prescale);

		write_byte(fd, MODE1, oldmode);

		usleep(10 * 1000);

		write_byte(fd, MODE1, oldmode | 0x80);

		close(fd);

	}
}

void PCA9685::setPWM(uint8_t led, int value) {
	setPWM(led, 0, value);
}


void PCA9685::setPWM(uint8_t led, int on_value, int off_value) {
	int fd = openfd(); if (fd != -1) {
		write_byte(fd, LED0_ON_L + LED_MULTIPLYER * led, on_value & 0xFF);

		write_byte(fd, LED0_ON_H + LED_MULTIPLYER * led, on_value >> 8);

		write_byte(fd, LED0_OFF_L + LED_MULTIPLYER * led, off_value & 0xFF);

		write_byte(fd, LED0_OFF_H + LED_MULTIPLYER * led, off_value >> 8);


		close(fd);
	}
}

uint8_t PCA9685::read_byte(int fd, uint8_t address) {
	return 0;
	uint8_t buff[BUFFER_SIZE];
	buff[0] = address;
	if (write(fd, buff, BUFFER_SIZE) != BUFFER_SIZE) {
		printf("I2C slave 0x%x failed to go to register 0x%x [read_byte():write %d]", _i2caddr, address, errno);
		return (-1);
	}
	else {
		if (read(fd, dataBuffer, BUFFER_SIZE) != BUFFER_SIZE) {
			printf("Could not read from I2C slave 0x%x, register 0x%x [read_byte():read %d]", _i2caddr, address, errno);
			return (-1);
		}
	}
}


void PCA9685::write_byte(int fd, uint8_t address, uint8_t data) {
	uint8_t buff[2];
	buff[0] = address;
	buff[1] = data;
	if (write(fd, buff, sizeof(buff)) != 2)
	{
		printf("Failed to write to I2C Slave 0x%x @ register 0x%x [write_byte():write %d]", _i2caddr, address, errno);
		usleep(5000);
	}
	else {
	}
}

int PCA9685::openfd() {
	int fd;
	if ((fd = open(busfile, O_RDWR)) < 0) {
		printf("Couldn't open I2C Bus %d [openfd():open %d]", _i2cbus, errno);
		return -1;
	}
	if (ioctl(fd, I2C_SLAVE, _i2caddr) < 0) {
		printf("I2C slave %d failed [openfd():ioctl %d]", _i2caddr, errno);
		return -1;
	}
	return fd;
}
