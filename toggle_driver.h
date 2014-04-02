/*
 * toggle_driver.h
 *
 *  Created on: Apr 1, 2014
 *      Author: stefan
 */

#ifndef TOGGLE_DRIVER_H_
#define TOGGLE_DRIVER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "inttypes.h"

#define UP 0x01
#define DOWN 0x02


typedef struct
{
	uint8_t pin1;
	uint8_t pin2;
} toggle_driver_t;

void toggle_driver_init(toggle_driver_t *driver, uint8_t pin1, uint8_t pin2);
void toggle_driver_move(toggle_driver_t *driver, uint8_t dir);
void toggle_driver_stop(toggle_driver_t *driver);


#ifdef __cplusplus
}
#endif


#endif /* TOGGLE_DRIVER_H_ */
