/*
 * bartender.h
 *
 *  Created on: Mar 31, 2014
 *      Author: stefan
 */

#ifndef BARTENDER_H_
#define BARTENDER_H_

#include "inttypes.h"
#include "stepper.h"
#include "toggle_driver.h"

#define STATUS_NONE 0x00
#define STATUS_MOVING 0x01
#define STATUS_POURING 0x02

typedef struct
{
	stepper_t *stepper;
	toggle_driver_t *toggler;
	uint8_t location;
	uint8_t status;
} bartender_t;

void bartender_init(bartender_t *bartender, stepper_t *stepper, toggle_driver_t *toggler, uint8_t location);
void bartender_move_to_location(bartender_t *bartender, uint8_t location);
void bartender_pour(bartender_t *bartender, uint8_t amount);

#endif /* BARTENDER_H_ */
