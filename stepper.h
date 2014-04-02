#ifndef STEPPER_H_
#define STEPPER_H_

#include "inttypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define DELAY 2

#define FORWARD 0
#define REVERSE 1

typedef struct
{
	uint8_t step;
	uint8_t pin0, pin1, pin2, pin3;
	unsigned long delay;
} stepper_t;

void stepper_init(stepper_t *stepper, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3);
void stepper_step(stepper_t *stepper, uint8_t direction);
void stepper_multi_step(stepper_t *stepper, uint16_t steps, uint8_t direction);
void stepper_release(stepper_t *stepper);


#ifdef __cplusplus
}
#endif


#endif /* STEPPER_H_ */
