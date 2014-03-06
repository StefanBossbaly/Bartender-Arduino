#include "stepper.h"
#include "Arduino.h"


void stepper_init(stepper_t *stepper, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3)
{
	stepper->pin0 = pin0;
	stepper->pin1 = pin1;
	stepper->pin2 = pin2;
	stepper->pin3 = pin3;
	stepper->step = 0;

	pinMode(stepper->pin0, OUTPUT);
	pinMode(stepper->pin1, OUTPUT);
	pinMode(stepper->pin2, OUTPUT);
	pinMode(stepper->pin3, OUTPUT);
}

void stepper_step(stepper_t *stepper, uint8_t direction)
{
	if (direction == FORWARD)
	{
		stepper->step++;

		if (stepper->step >= 4)
		{
			stepper->step = 0;
		}
	}
	else
	{
		stepper->step--;

		if (stepper->step < 0)
		{
			stepper->step = 3;
		}
	}

	switch (stepper->step)
	{
	case 0:
		digitalWrite(stepper->pin0, HIGH);
		digitalWrite(stepper->pin1, LOW);
		digitalWrite(stepper->pin2, HIGH);
		digitalWrite(stepper->pin3, LOW);
		break;
	case 1:
		digitalWrite(stepper->pin0, LOW);
		digitalWrite(stepper->pin1, HIGH);
		digitalWrite(stepper->pin2, HIGH);
		digitalWrite(stepper->pin3, LOW);
		break;
	case 2:
		digitalWrite(stepper->pin0, LOW);
		digitalWrite(stepper->pin1, HIGH);
		digitalWrite(stepper->pin2, LOW);
		digitalWrite(stepper->pin3, HIGH);
		break;
	case 3:
		digitalWrite(stepper->pin0, HIGH);
		digitalWrite(stepper->pin1, LOW);
		digitalWrite(stepper->pin2, LOW);
		digitalWrite(stepper->pin3, HIGH);
		break;
	}

	delay(5);
}

void stepper_release(stepper_t *stepper)
{
	digitalWrite(stepper->pin0, HIGH);
	digitalWrite(stepper->pin1, HIGH);
	digitalWrite(stepper->pin2, HIGH);
	digitalWrite(stepper->pin3, HIGH);
}
