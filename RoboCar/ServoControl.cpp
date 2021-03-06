#include  "ServoControl.h"
#include "PCA9685.h"
#include <cstdio>
#include <unistd.h>

int MinPulse = 200;
int MaxPulse = 700;

int MaxLeft = 350;
int MaxRight = 450;
int Middle = 400;

int Current_x = 0;
int Current_y = 0;
int Xmin, Ymin, Xmax, Ymax, home_x, home_y;

int EN_M0 = 4;
int EN_M1 = 5;

int Motor0_A = 0;// 11;//  # pin11
int Motor0_B = 1;// 12;//  # pin12
int Motor1_A = 2;// 13;//  # pin13
int Motor1_B = 3;// 15;//  # pin15

PCA9685 pwm;

void setup()
{
	pinMode(Motor0_A, OUTPUT);
	pinMode(Motor1_A, OUTPUT);
	pinMode(Motor0_B, OUTPUT);
	pinMode(Motor1_B, OUTPUT);
	pinMode(29, OUTPUT);

	printf("Testing testing\n"); //make sure you use the right address values. 

	pwm.init(1, 0x40);
	usleep(1000);
	printf("Setting frequency..\n");
	pwm.setPWMFreq(61);
	usleep(10000);
	int count = 0;

	pwm.setPWM(14, 0, 450);
	delay(500);
	pwm.setPWM(15, 0, 250);
	delay(500);

	pwm.setPWM(0, 0, MaxLeft);

	delay(1000);

	pwm.setPWM(0, 0, MaxRight);

	delay(1000);

	pwm.setPWM(0, 0, Middle);

	delay(1000);

	// Motor Speed
	pwm.setPWM(EN_M0, 0, 4000);
	pwm.setPWM(EN_M1, 0, 4000);


	// Pin29 Standby f�r Motor (vorl�ufig)
	digitalWrite(29, HIGH);


	printf("And Go 1\n");
	forwardWithSpeed(70);
	printf("And Go 2\n");

	delay(5000);
	stop();

	KopfKreisen();


	while (count++ < 5)
	{
		pwm.setPWM(14, 0, 400);
		delay(100);
		pwm.setPWM(14, 0, 500);
		delay(100);
	}
	count = 0;

	while (count++ < 1)
	{
		pwm.setPWM(14, 0, 250); // 14 = 250 Rechts
		delay(500);
		//pwm.setPWM(15, 0, 300); // 15 = Hoch / Runter
		//usleep(1000 * 1000);
		pwm.setPWM(14, 0, 700); // 700 = Links
		delay(500);
		//pwm.setPWM(15, 0, 700);
		//usleep(1000 * 1000);
	}
	pwm.setPWM(14, 0, 450);
	delay(100);
	pwm.setPWM(15, 0, 250);
	delay(1000);
	pwm.setPWM(15, 0, 550);
	delay(1000);
	pwm.setPWM(14, 0, 450);
	delay(100);
	pwm.setPWM(15, 0, 300);
	printf("\n");



	//int offset_x = -17;
	//int offset_y = 25;
	///*
	//try :
	//for line in open('config') :
	//if line[0:8] == 'offset_x' :
	//offset_x = int(line[11:-1])
	//print 'offset_x =', offset_x
	//if line[0:8] == 'offset_y' :
	//offset_y = int(line[11:-1])
	//print 'offset_y =', offset_y
	//except :
	//pass*/
	//Xmin = MinPulse + offset_x;
	//Xmax = MaxPulse + offset_x;
	//Ymin = MinPulse + offset_y;
	//Ymax = MaxPulse + offset_y;
	//home_x = (Xmax + Xmin) / 2;
	//home_y = Ymin + 80;
	///*pwm = servo.PWM()           # Initialize the servo controller.*/
	//int pcaHandle = wiringPiI2CSetup(0x40);
	//init(pcaHandle);
	//home_x_y(pcaHandle);
}
//# ==========================================================================================
//# Control the servo connected to channel 14 of the servo control board to make the camera
//# turning towards the positive direction of the x axis.
//# ==========================================================================================
void move_decrease_x(int pcaHandle)
{
	Current_x += 25;
	if (Current_x > Xmax)
		Current_x = Xmax;
	//set_value(pcaHandle, 14, 0, Current_x);//   # CH14 < --->X axis
}
//# ==========================================================================================
//# Control the servo connected to channel 14 of the servo control board to make the camera
//# turning towards the negative direction of the x axis.
//# ==========================================================================================
void move_increase_x(int pcaHandle)
{
	Current_x -= 25;
	if (Current_x <= Xmin)
		Current_x = Xmin;
	//set_value(pcaHandle, 14, 0, Current_x);
}
//# ==========================================================================================
//# Control the servo connected to channel 15 of the servo control board to make the camera
//# turning towards the positive direction of the y axis.
//# ==========================================================================================
void move_increase_y(int pcaHandle)
{
	Current_y += 25;
	if (Current_y > Ymax)
		Current_y = Ymax;
	//set_value(pcaHandle, 15, 0, Current_y);//   # CH15 < --->Y axis
}
/*# ==========================================================================================
# Control the servo connected to channel 15 of the servo control board to make the camera
# turning towards the negative direction of the y axis.
# ==========================================================================================*/
void move_decrease_y(int pcaHandle)
{
	Current_y -= 25;
	if (Current_y <= Ymin)
		Current_y = Ymin;
	//set_value(pcaHandle, 15, 0, Current_y);
}
//# ==========================================================================================
//# Control the servos connected with channel 14 and 15 at the same time to make the camera
//# move forward.
//# ==========================================================================================
void home_x_y(int pcaHandle)
{
	Current_y = home_y;
	Current_x = home_x;
	//set_value(pcaHandle, 14, 0, Current_x);
	//set_value(pcaHandle, 15, 0, Current_y);
}
void calibrate(int pcaHandle, int x, int y)
{
	//set_value(pcaHandle, 14, 0, (MaxPulse + MinPulse) / 2 + x);
	//set_value(pcaHandle, 15, 0, (MaxPulse + MinPulse) / 2 + y);
}

void test(int pcaHandle)
{
	home_x_y(pcaHandle);
	delay(500);
	int i;
	for (i = 0; i < 9; i++)
	{
		move_increase_x(pcaHandle);
		move_increase_y(pcaHandle);
		delay(500);
	}
	for (i = 0; i < 9; i++)
	{
		move_decrease_x(pcaHandle);
		move_decrease_y(pcaHandle);
		delay(500);
	}
	setup();
	home_x_y(pcaHandle);
}


void setSpeed(int speed)
{
	speed *= 40;
	pwm.setPWM(EN_M0, 0, speed);
	pwm.setPWM(EN_M1, 0, speed);
}

//# ===========================================================================
//# Control the DC motor to make it rotate clockwise, so the car will
//# move forward.
//# ===========================================================================

void motor0(bool x)
{
	if (x)
	{
		digitalWrite(Motor0_A, LOW);
		digitalWrite(Motor0_B, HIGH);
	}
	else if (!x)
	{
		digitalWrite(Motor0_A, HIGH);
		digitalWrite(Motor0_B, LOW);
	}
	else
		printf("Config Error");
}
void motor1(bool x)
{
	if (x)
	{
		digitalWrite(Motor1_A, LOW);
		digitalWrite(Motor1_B, HIGH);
	}
	else if (!x)
	{
		digitalWrite(Motor1_A, HIGH);
		digitalWrite(Motor1_B, LOW);
	}
}
void forward()
{
	motor0(false);
	motor1(false);
}
void backward()
{
	motor0(true);
	motor1(true);
}

void forwardWithSpeed(int spd)
{
	setSpeed(spd);
	motor0(false);
	motor1(false);
}
void backwardWithSpeed(int spd)
{
	setSpeed(spd);
	motor0(true);
	motor1(true);
}
void stop()
{
	digitalWrite(Motor1_A, LOW);
	digitalWrite(Motor1_B, LOW);
	digitalWrite(Motor0_A, LOW);
	digitalWrite(Motor0_B, LOW);

	//for pin in pins :
	//digitalWrite(pin, LOW);
}

void KopfKreisen()
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		pwm.setPWM(14, 0, 250); // 14 = 250 Rechts
		delay(150);
		pwm.setPWM(15, 0, 500); // 15 = Hoch / Runter
		delay(150);
		pwm.setPWM(14, 0, 700); // 700 = Links
		delay(150);
		pwm.setPWM(15, 0, 300); // 15 = Hoch / Runter
		delay(150);
	}
}
