#include "RoboStart.h"
#include "LedControl.h"

void Blink_Change()
{
	int x = 0;
	do
	{
		digitalWrite(6, HIGH);
		delay(DELAY);
		digitalWrite(6, LOW);
		digitalWrite(10, HIGH);
		delay(DELAY);
		digitalWrite(10, LOW);
	} while (x++ < 25);
}

