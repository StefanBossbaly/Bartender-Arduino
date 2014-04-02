#include "bartender.h"

#include "Arduino.h"

#include <math.h>
#include <util/atomic.h>

void bartender_init(bartender_t *bartender, stepper_t *stepper, toggle_driver_t *toggler, uint8_t location)
{
	bartender->stepper = stepper;
	bartender->toggler = toggler;
	bartender->location = location;
}


void bartender_move_to_location(bartender_t *bartender, uint8_t location)
{
	// Make sure that we are not doing anything
	if (bartender->status != STATUS_NONE)
	{
		return;
	}

	// We are moving
	bartender->status = STATUS_MOVING;

	for (uint8_t i = 0; i < fabs(bartender->location - location); i++)
	{
		if (bartender->location - location > 0)
		{
			stepper_multi_step(bartender->stepper, 500, FORWARD);
		}
		else
		{
			stepper_multi_step(bartender->stepper, 500, REVERSE);;
		}
	}

	// We are done
	bartender->status = STATUS_NONE;
}

void bartender_pour(bartender_t *bartender, uint8_t amount)
{
	// Make sure that we are not doing anything
	if (bartender->status != STATUS_NONE)
	{
		return;
	}

	// We are pouring
	bartender->status = STATUS_POURING;

	digitalWrite(7, HIGH);
	digitalWrite(8, LOW);
	delay(5000);

	digitalWrite(7, LOW);
	digitalWrite(8, HIGH);
	delay(5000);

	digitalWrite(7, LOW);
	digitalWrite(8, LOW);

	// We are done
	bartender->status = STATUS_NONE;

}
