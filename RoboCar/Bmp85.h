#ifndef BMP85_H
#define BMP85_H

#include  "RoboStart.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


void read_calibration_values(int fd);
void get_readings(long UT, long UP);
void get_temp_pressure(int i2c_BMP085_Handle, double* values);

#endif
