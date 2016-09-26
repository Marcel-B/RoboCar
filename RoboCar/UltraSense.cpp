#include "UltraSense.h"


double get_distance()
{
	digitalWrite(TRIGGER, HIGH);
	delay(.01);
	digitalWrite(TRIGGER, LOW);


	struct timeval t1, t2;
	long long elapsedTime;

	/* Startwert */
	gettimeofday(&t1, NULL);


	while (digitalRead(ECHO) == 0)
		gettimeofday(&t1, NULL);

	while (digitalRead(ECHO) == 1)
		gettimeofday(&t2, NULL);

	/* Berechne die verbrauchte Zeit in Microsekunden */
	elapsedTime = ((t2.tv_sec * 1000000) + t2.tv_usec)
		- ((t1.tv_sec * 1000000) + t1.tv_usec);

	// printf("Aufruf dauerte  %lld s\n", elapsedTime);

	// mit der Schallgeschwindigkeit(34300 cm / s) multiplizieren
	// und durch 2 teilen, da hin und zurueck
	double distanz = (elapsedTime * 34300) / 2;
	return distanz / 1000000;
}
