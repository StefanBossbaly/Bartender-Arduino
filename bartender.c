#include "bartender.h"

#include "Arduino.h"

#include <math.h>
#include <util/atomic.h>

uint16_t step_distances[13] = {900, 635, 675, 675, 660, 675, 675, 675, 675, 675, 645, 675, 675};

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

	uint8_t direction = FORWARD;

	if (bartender->location > location)
	{
		direction = REVERSE;
	}

	// While the location doesn't equal location
	while (bartender->location != location)
	{
		uint16_t steps = 0;

		if (direction == FORWARD)
		{
			steps = step_distances[bartender->location];
		}
		else
		{
			steps = step_distances[bartender->location - 1];
		}

		stepper_multi_step(bartender->stepper, steps, direction);

		if (direction == FORWARD)
		{
			bartender->location++;
		}
		else
		{
			bartender->location--;
		}
	}

	// Release the stepper
	stepper_release(bartender->stepper);

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

	toggle_driver_move(bartender->toggler, UP);
	delay(5000);

	toggle_driver_move(bartender->toggler, DOWN);
	delay(5000);

	toggle_driver_stop(bartender->toggler);

	// We are done
	bartender->status = STATUS_NONE;
}
