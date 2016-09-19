
#include "Gyroscope.h"

double dist(double a, double b)
{
	return sqrt((a*a) + (b*b));
}

double get_y_rotation(double x, double y, double z)
{
	double result = atan2(x, dist(y, z));
	return -result * halfC;
}

double get_x_rotation(double x, double y, double z)
{
	double radians = atan2(y, dist(x, z));
	return radians * halfC;
}

void get_gyro(double* values, int i2c_Handle)
{
	double xData, yData, zData;
	double xD, yD, zD;
	double xS, yS, zS;
	double xRot, yRot;

	wiringPiI2CWriteReg8(i2c_Handle, 0x6b, 0);

	xData = wiringPiI2CReadReg16(i2c_Handle, 0x43);
	yData = wiringPiI2CReadReg16(i2c_Handle, 0x45);
	zData = wiringPiI2CReadReg16(i2c_Handle, 0x47);

	values[0] = xData / 131.0;
	values[1] = yData / 131.0;
	values[2] = zData / 131.0;

	xD = wiringPiI2CReadReg16(i2c_Handle, 0x3b);
	yD = wiringPiI2CReadReg16(i2c_Handle, 0x3d);
	zD = wiringPiI2CReadReg16(i2c_Handle, 0x3f);

	xS = xD / 16384.0;
	yS = yD / 16384.0;
	zS = zD / 16384.0;

	values[3] = xS;
	values[4] = yS;
	values[5] = zS;


	xRot = get_x_rotation(xS, yS, zS);
	yRot = get_y_rotation(xS, yS, zS);

	values[6] = xRot;
	values[7] = yRot;

	//printf("X= %f | Y= %f | Z= %f | AX= %f | AY= %f | AZ= %f | RotX= %f | RotY= %f\n", xScaled, yScaled, zScaled, xS, yS, zS, xRot, yRot);
	printf("RotX = %f | RotY = %f\n", xRot, yRot);
}

