#include "stepper.h"

stepper_t stepper;

void setup()
{
	stepper_init(&stepper, 2, 3, 4, 5);
}

void loop()
{
	stepper_step(&stepper, REVERSE);
}