/**
 * @file   bartender.h
 * @brief  Defines the functions that the bartender can perform.
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 * This is where all the upper level logic functions of the bartender
 * are defined. These functions hope to encapsulate the logic of the
 * other functions. The bartender structure hold all of the information
 * that is associated with the bartender. The first item is the status. This
 * is the current action that the bartender is performing. The defined status
 * are found in this header file which are STATUS_NONE, STATUS_MOVING and
 * STATUS_POURING. Note that when updating the status make sure that we are
 * doing it using atomic functions since we could overwrite the status value
 * from a ISR.
 */

#ifndef BARTENDER_H_
#define BARTENDER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "inttypes.h"
#include "stepper.h"
#include "toggle_driver.h"

// --------------------------------------------------------------------
// Status Definitions
// --------------------------------------------------------------------

/**
 * The bartender is currently doing nothing.
 */
#define STATUS_NONE 0x00

/**
 * The bartender is currently moving from one location to another.
 */
#define STATUS_MOVING 0x01

/**
 * The bartender is currently pouring liquid from one of its dispensers.
 */
#define STATUS_POURING 0x02

/**
 * The bartender has be interrupted and needs to stop doing any kind of interrupt
 * sensitive activities.
 */
#define STATUS_INT 0x03

/**
 * The bartender has been stopped and needs the bartender_reset() function called in
 * order to resume normal operation.
 */
#define STATUS_STOPPED 0x04

/**
 * The structure of a bartender. Hold all the attributes that a bartender
 * has. Please look at the file explanation for more documentation.
 */
typedef struct
{
	stepper_t *stepper; /**< the stepper motor that drives the linear actuator
	 	 	 	 	 	 	 of the drink plate*/
	toggle_driver_t *toggler; /**< the motor driver of the vertical linear actuator
	 	 	 	 	 	 	 	 that dispenses liquid */
	uint8_t location; /**< the current location of the drink plate of the bartender */
	volatile uint8_t status; /**< the status of the bartender as defined by the status
	 	 	 	 	 	 definitions found in this file. */
} bartender_t;

/**
 * @name    Bartender Initialization
 * @brief   Initializes the bartender structure
 * @ingroup bartender
 *
 * This function setups up all the initial values for the bartender_t structure.
 * You must call this function on a structure before calling any other of the
 * bartender functions of said structure.
 *
 * @param [in] bartender The bartender to be initialized
 * @param [in] stepper the stepper that drives the horizontal linear
 * actuator of the bartender
 * @param [in] toggler the vertical linear actuator that dispenses liquid
 * @param [in] location the starting location of the bartender
 *
 */
void bartender_init(bartender_t *bartender, stepper_t *stepper, toggle_driver_t *toggler, uint8_t location);

/**
 * @name    Bartender Move to Location
 * @brief   Moves the drink platform to a new location
 * @ingroup bartender
 *
 * This function move the the drink platform that is attached to the
 * vertical linear actuator to the location that is passed into this
 * function. Each drink dispenser has a location label starting at
 * 1 and ending at 12. 0 is the magic value for the home location.
 *
 * @warning This function returns E_BUSY if the status of the bartender
 * is not STATUS_NONE.
 *
 * @param [in] bartender The bartender that is being operated on
 * @param [in] location the new location that the bartender should
 * go to
 *
 * @retval E_NO_ERROR no error occurred and the function was completed
 * successfully
 * @retval E_BUSY if the status of the bartender was not STATUS_NONE before
 * the function was called
 */
uint8_t bartender_move_to_location(bartender_t *bartender, uint8_t location);

/**
 * @name    Bartender Pour
 * @brief   Pours an amount of liquid from the current location
 * @ingroup bartender
 *
 * The bartender will pour the specified amount from the dispenser
 * that the bartender is currently at.
 *
 * @warning This function returns E_BUSY if the status of the bartender
 * is not STATUS_NONE.
 *
 * @param [in] bartender The bartender that is being operated on
 * @param [in] amount the amount of liquid that the bartender should
 * pour from the dispenser.
 *
 * @retval E_NO_ERROR no error occurred and the function was completed
 * successfully
 * @retval E_BUSY if the status of the bartender was not STATUS_NONE before
 * the function was called
 */
uint8_t bartender_pour(bartender_t *bartender, uint8_t amount);

/**
 * @name    Bartender Stop
 * @brief   Stops any operation of the bartender
 * @ingroup bartender
 *
 * This stops the bartender from processing any current commands.
 *
 * @note That this stops the bartender in the current state. (If the
 * bartender was moving or if the bartender was pouring this function
 * will stop any operation in the current state).
 *
 * @param [in] bartender The bartender that is being operated on
 *
 * @retval E_NO_ERROR no error occurred and the function was completed
 * successfully
 */
uint8_t bartender_stop(bartender_t *bartender);

/**
 * @name    Bartender Reset
 * @brief   Resets a stopped bartender
 * @ingroup bartender
 *
 * This function resets the bartender from the stopped state. It first
 * lowers the linear actuator used for pouring the drinks. Next it moves
 * the drink plate back to the home position. It then resets the status
 * and the location of the bartender. This function must be called in order
 * for the bartender to process commands after the stop function is called.
 *
 * @warning This function returns E_INV_CALL if the status of the bartender
 * is not STATUS_STOPPED.
 *
 * @param [in] bartender The bartender that is being operated on
 *
 * @retval E_NO_ERROR no error occurred and the function was completed
 * successfully
 * @retval E_INV_CALL if the status of the bartender is not STATUS_STOPPED
 */
uint8_t bartender_reset(bartender_t *bartender);

#ifdef __cplusplus
}
#endif

#endif /* BARTENDER_H_ */
