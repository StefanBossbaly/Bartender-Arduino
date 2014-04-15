/**
 * @file   handler.h
 * @brief  Handles messages that are received by the microprocessor.
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 * The handler takes a message that was received by the microprocessor and calls
 * the appropriate bartender function. The handler also takes care of responding to
 * the control device. When a message is received by the handler it first determines
 * if the message is valid. If the message is invalid (malformed) then it responds
 * to the control device with an error. If the message is valid it determines what
 * command the message contains and calls the appropriate command handler. Each
 * command handler will handle errors that can occur with each command (example
 * a location of 13 in the CMD_MOVE) and respond with an error message to the control
 * device.
 */
#ifndef HANDLER_H_
#define HANDLER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stepper.h"
#include "bartender.h"
#include "inttypes.h"

/**
 *
 */
typedef struct
{
	bartender_t *bartender;
} handler_t;

/**
 * @name    Initialize Handler
 * @brief   Sets up the default values for the handler structure.
 * @ingroup handler
 *
 * Sets up a handler_t.
 *
 * @param [in] handler the handler that will be initialized
 * @param [in] bartender the bartender that is associated with the handler
 *
 */
void handler_init(handler_t *handler, bartender_t *bartender);

/**
 * @name    Handle Received Message
 * @brief   Calls the bartender function specified by the message.
 * @ingroup handler
 *
 * This is the main function of the handle functions. It takes in a message
 * of length MSG_SIZE and calls the bartender function specified by the inputed
 * message. This function handles if the message is malformed and will send back
 * a response of RSP_MAL_MSG if the message is malformed. Please note that this
 * function is blocking. An example is if a message of CMD_MOVE is passed in to
 * the handler the function will not return until the drink plate has moved to
 * the new location.
 *
 * @param [in] handler the instance of the handler that will be doing the
 * processing
 * @param [in] cmd the command to be processed. Its length must be MSG_SIZE
 *
 */
void handler_handle(handler_t *handler, uint8_t *cmd);


#ifdef __cplusplus
}
#endif

#endif /* HANDLER_H_ */
