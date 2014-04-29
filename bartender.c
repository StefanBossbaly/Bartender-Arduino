#include "bartender.h"

#include "Arduino.h"
#include "error.h"

#include <math.h>
#include <util/atomic.h>

/**
 * Step distance array. Hardik can't measure.
 */
uint16_t step_distances[13] = {880, 635, 675, 675, 660, 675, 675, 675, 675, 675, 645, 675, 675};

void bartender_init(bartender_t *bartender, stepper_t *stepper, toggle_driver_t *toggler, uint8_t location)
{
	bartender->stepper = stepper;
	bartender->toggler = toggler;
	bartender->location = location;
}


uint8_t bartender_move_to_location(bartender_t *bartender, uint8_t location)
{
	// Make sure that we are not doing anything
	if (bartender->status != STATUS_NONE)
	{
		return E_BUSY;
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

		// Get the number of steps to the new location
		if (direction == FORWARD)
		{
			steps = step_distances[bartender->location];
		}
		else
		{
			steps = step_distances[bartender->location - 1];
		}

		// Special case. Keep going until we hit the bump sensor
		// Side note: I personally disagree with this case but the hardware guys
		// demand I implement it. Hooray for relying on safety systems for normal
		// operation
		if (location == 0 && bartender->location == 1)
		{
			steps = 0xFFFF;
		}

		// Now step baby step (as long as our status doesn't change)
		for (uint16_t i = 0; (i < steps) && (bartender->status == STATUS_MOVING); i++)
		{
			stepper_step(bartender->stepper, direction);
		}

		// We were interrupted
		if (bartender->status == STATUS_INT)
		{
			stepper_release(bartender->stepper);
			bartender->location = 0;
			bartender->status = STATUS_NONE;
			return E_NO_ERROR;
		}

		// Update the location variable
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

	return E_NO_ERROR;
}

uint8_t bartender_pour(bartender_t *bartender, uint8_t amount)
{
	// Make sure that we are not doing anything
	if (bartender->status != STATUS_NONE)
	{
		return E_BUSY;
	}

	// We are pouring
	bartender->status = STATUS_POURING;

	// Up. Delay. Down. Delay.
	for (uint8_t i = 0; i < amount; i++)
	{
		toggle_driver_move(bartender->toggler, UP);
		delay(5000);

		toggle_driver_move(bartender->toggler, DOWN);
		delay(5000);

		toggle_driver_stop(bartender->toggler);
	}

	// We are done
	bartender->status = STATUS_NONE;

	return E_NO_ERROR;
}
