#include "Arduino.h"
#include "toggle_driver.h"

void toggle_driver_init(toggle_driver_t *driver, uint8_t pin1, uint8_t pin2)
{
	driver->pin1 = pin1;
	driver->pin2 = pin2;

	pinMode(driver->pin1, OUTPUT);
	pinMode(driver->pin2, OUTPUT);
}

void toggle_driver_move(toggle_driver_t *driver, uint8_t dir)
{
	if (dir == UP)
	{
		digitalWrite(driver->pin1, HIGH);
		digitalWrite(driver->pin2, LOW);
	}
	else
	{
		digitalWrite(driver->pin1, LOW);
		digitalWrite(driver->pin2, HIGH);
	}
}

void toggle_driver_stop(toggle_driver_t *driver)
{
	digitalWrite(driver->pin1, LOW);
	digitalWrite(driver->pin2, LOW);
}
