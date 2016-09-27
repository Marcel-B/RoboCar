#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include "RoboStart.h"
void test(int pcaHandle);
void calibrate(int pcaHandle, int x, int y);
void home_x_y(int pcaHandle);
void move_decrease_y(int pcaHandle);
void move_increase_y(int pcaHandle);
void move_increase_x(int pcaHandle);
void move_decrease_x(int pcaHandle);
void setup();
void motor0(bool x);
void motor1(bool x);
void forward();
void backward();
void forwardWithSpeed(int spd);
void backwardWithSpeed(int spd);
void stop();



#endif

