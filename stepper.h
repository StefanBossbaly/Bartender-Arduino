/**
 * @file   stepper.h
 * @brief  Defines a unidirectional stepper motor and the operations that can
 * be performed on it.
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 * Defines the a unidirectional stepper motor and the operations that can
 * be performed on it. The stepper motor is connected to the microprocessor
 * via 4 digital output pins that control the motor driver (H-Bridge).
 */
#ifndef STEPPER_H_
#define STEPPER_H_

#include "inttypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * The default delay between steps (in milliseconds)
 */
#define DELAY 2

/**
 * The forward direction
 */
#define FORWARD 0

/**
 * The reverse direction
 */
#define REVERSE 1

/**
 * A structure that represents a stepper motor
 */
typedef struct
{
	uint8_t step; /**< the current step sequence the motor is at */
	uint8_t pin0, pin1, pin2, pin3; /**< the digital output pins connected to the control lines of the motor driver */
	unsigned long delay; /**< the delay between steps */
} stepper_t;

/**
 * @name    Initialize the Stepper
 * @brief   Sets up the default values for the steper structure.
 * @ingroup stepper
 *
 * Sets up a stepper_t.
 *
 * @param [in] stepper the stepper that will be initialized
 * @param [in] pin0 the first digital control line
 * @param [in] pin1 the second digital control line
 * @param [in] pin2 the third digital control line
 * @param [in] pin3 the fourth digital control line
 */
void stepper_init(stepper_t *stepper, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3);

/**
 * @name    Step the Stepper
 * @brief   Steps the stepper in the given direction.
 * @ingroup stepper
 *
 * Steps the stepper in the given direction.
 *
 * @note This function does take into account the delay field in
 * the stepper_t function.
 *
 * @param [in] stepper the stepper that will be initialized
 * @param [in] pin0 the first digital control line
 * @param [in] pin1 the second digital control line
 * @param [in] pin2 the third digital control line
 * @param [in] pin3 the fourth digital control line
 */
void stepper_step(stepper_t *stepper, uint8_t direction);

/**
 * @name    Step the Stepper for Multiple Steps
 * @brief   Steps the stepper in the given direction for a number of steps.
 * @ingroup stepper
 *
 * Steps the stepper the given number of steps in the specified direction.
 *
 * @param [in] stepper the stepper that will be initialized
 * @param [in] steps the amount of steps the stepper will step
 * @param [in] direction the direction in which stepper will step
 */
void stepper_multi_step(stepper_t *stepper, uint16_t steps, uint8_t direction);

/**
 * @name    Release the Stepper
 * @brief   Release the stepper motor.
 * @ingroup stepper
 *
 * Writes logical LOW to all of the control lines so that the motor driver no
 * longer pulls any current from the power lines.
 *
 * @param [in] stepper the stepper that will be released
 */
void stepper_release(stepper_t *stepper);


#ifdef __cplusplus
}
#endif


#endif /* STEPPER_H_ */
