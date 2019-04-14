all: RoboStart.o ServoControl.o LedControl.o Display.o Dht22.o Bmp85.o PCA9685.o
	gcc -o all RoboStart.o ServoControl.o LedControl.o Display.o Dht22.o Bmp85.o PCA9685.o -lwiringPi

PCA9685.o: PCA9685.cpp
	gcc -c PCA9685.cpp

Bmp85.o: Bmp85.cpp
	gcc -c Bmp85.cpp

Dht22.o: Dht22.cpp
	gcc -c Dht22.cpp

Display.o: Display.cpp
	gcc -c Display.cpp

LedControl.o: LedControl.cpp
	gcc -c LedControl.cpp

ServoControl.o: ServoControl.cpp
	gcc -c ServoControl.cpp

RoboStart.o: RoboStart.cpp
	gcc -c RoboStart.cpp

