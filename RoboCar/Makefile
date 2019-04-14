all: main.o servo.o led.o display.o dht.o bmp.o pca.o
	gcc -o all main.o servo.o led.o display.o dht.o bmp.o pca.o

pca.o: PCA9685.cpp
	gcc -c PCA9685.cpp

bmp.o: Bmp85.cpp
	gcc -c Bmp85.cpp

dht.o: Dht22.cpp
	gcc -c Dht22.cpp

display.o: Display.cpp
	gcc -c Display.cpp

led.o: LedControl.cpp
	gcc -c LedControl.cpp

servo.o: ServoControl.cpp
	gcc -c ServoControl.cpp

main.o: RoboStart.cpp
	gcc -c RoboStart.cpp

