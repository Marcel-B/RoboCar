#include "RoboStart.h"
#include "LedControl.h"
#include "Gyroscope.h"
#include "UltraSense.h"
#include "Bmp85.h"
#include "Dht22.h"
#include "ServoControl.h"
#include "Display.h"
#include <string>
#include <sstream>

int main(void)
{
	int result = wiringPiSetup();
	if (result == -1)
		return 1;

	double dist;

	int i2c_GryscopeHandle = wiringPiI2CSetup(0x68);
	int i2c_BMP085_Handle = wiringPiI2CSetup(0x77);
	setup();
	printf("Handel No: %d\n", i2c_GryscopeHandle);

	pinMode(LEDLEFT, OUTPUT);
	pinMode(LEDRIGHT, OUTPUT);
	pinMode(TRIGGER, OUTPUT);
	pinMode(ECHO, INPUT);

	double* gyroValues = (double*)malloc(sizeof(double) * 8);
	double* tempPressValues = (double*)malloc(sizeof(double) * 3);
	double* tempHumiValues = (double*)malloc(sizeof(double) * 2);

	//int i = 0;
	int display_handle = wiringPiI2CSetup(0x3c);
	Display* dis = new Display(display_handle);

	std::string foo = "Hallo Welt";
	dis->set_row(foo.c_str(), foo.length());

	do {
		get_gyro(gyroValues, i2c_GryscopeHandle);
		get_temp_pressure(i2c_BMP085_Handle, tempPressValues);
		read_dht22_dat(tempHumiValues);
		dist = get_distance();
		//for (i = 0; i < 8; i++)
		//  printf("Val %d = %f\n", i, gyroValues[i]);
		printf("+++++++++\n");
		printf("Temp     : %f\n", tempPressValues[0]);
		printf("Temp     : %f\n", tempHumiValues[0]);
		printf("Humidity : %f\n", tempHumiValues[1]);
		printf("Pressure : %f\n", tempPressValues[1]);
		printf("SeaLevel : %f\n", tempPressValues[2]);
		printf("Distance : %f\n", dist);
		//Blink_Change();

		std::stringstream ss;
		ss << "Temp:..." << tempHumiValues[0];
		std::string temper = ss.str();

		dis->clear();

		dis->set_row(temper.c_str(), temper.length());

		std::stringstream sss;
		sss << "Humi:..." << tempHumiValues[1];
		
		std::string tomper = sss.str();
		dis->set_row(tomper.c_str(), tomper.length());



		delay(5000);
	} while (1);
	free(gyroValues);
	free(tempPressValues);
	free(tempHumiValues);
	free(dis);
	return 0;
}
