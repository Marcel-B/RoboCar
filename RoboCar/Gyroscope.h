#ifndef GYROSCOPE_H
#define GYROSCOPE_H
#include <stdio.h>
#include <math.h>
#include "RoboStart.h"

static const double halfC = 180 / 3.14159265;

void get_gyro(double* values, int i2c_Handle);
double get_x_rotation(double x, double y, double z);
double get_y_rotation(double x, double y, double z);
double dist(double a, double b);

#endif

