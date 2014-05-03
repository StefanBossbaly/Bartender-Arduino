/**
 * @file   protocol.h
 * @brief  Defines the communication protocol between the bartender
 * and the control device.
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 * This is where the protocol between the bartender and the control device is defined. The
 * data is organized into structured format called a message. The message has a size of MSG_SIZE.
 * The message structure can be broken down into different sections as shown below.
 *
 * [START] [TYPE] [CMD] [RSP_CODE] [CONTENT] [STOP]
 *
 * The first and the last section of a message are called the start and stop bytes and are
 * defined as MSG_START and MSG_END at location I_START and I_END respectively. The message
 * must have these start and stop bytes so in case we drop a byte during transmission we are
 * able to tell which message is malformed.
 *
 * The next section is the Type section at location I_TYPE. The type header defined what kind
 * of message we are sending or receiving. If we are issuing a command then the type header is
 * set to TYPE_CMD and if we are responding to a command then the type header should be set to
 * TYPE_RSP.
 *
 * The next section is the command section at location I_CMD. The acceptable value of this command
 * is any of the command values (CMD_STOP, CMD_MOVE, CMD_POUR, CMD_STATUS, CMD_LOCATION). If
 * the message is of type TYPE_CMD then the command section represents the command that the
 * message is issuing. If the message is of type TYPE_RSP then the command section represents
 * the command that the message is responding to or BLANK if the response is not responding
 * to a command.
 *
 * The next section is the response code section located at I_RSP_CODE. This section lets
 * the response define a response code that defines the status of the response. This is
 * like the http status code section.
 * If the message is of type TYPE_CMD then the response code section is BLANK.
 *
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "inttypes.h"

// -------------------------------------------------------------------------------------------
// General Section
// -------------------------------------------------------------------------------------------

/**
 * The size of the message in bytes
 */
#define MSG_SIZE 32

/**
 * Default value if a message header is not required
 */
#define BLANK 0x00

// -------------------------------------------------------------------------------------------
// Start and Stop Section
// -------------------------------------------------------------------------------------------

/**
 * Location of the start byte
 */
#define I_START 0x00

/**
 * Location of the stop byte
 */
#define I_END 0x1F

/**
 * Value of the start byte
 */
#define MSG_START 0xFF

/**
 * Value of the stop byte
 */
#define MSG_END 0xFE

// -------------------------------------------------------------------------------------------
// Type Section
// -------------------------------------------------------------------------------------------

/**
 * Location of the type header
 */
#define I_TYPE 0x01

/**
 * Value if the message is a response
 */
#define TYPE_RSP 0x01

/**
 * Value if the message is a command
 */
#define TYPE_CMD 0x02

// -------------------------------------------------------------------------------------------
// Command Section
// -------------------------------------------------------------------------------------------

/**
 * Location of the command byte
 */
#define I_CMD 0x02

/**
 * Stop Command
 *
 * Tells the bartender to stop any actions
 * and any pending actions.
 */
#define CMD_STOP 0x01

/**
 * Move Command <location>
 *
 * Tells the bartender to move to a pin location
 * 0 is a magic value for the home position
 */
#define CMD_MOVE 0x02

/**
 * The parameter of the move command. Must be in between 0-12.
 */
#define PARAM_MOVE_LOC 0x04

/**
 * Pour Command <amount>
 *
 * Tells the bartender to pour an amount from the
 * current location
 */
#define CMD_POUR 0x03

/**
 * The parameter of the pour command. Defines the amount of shots to be poured
 * into the glass.
 */
#define PARAM_POUR_AMOUNT 0x04

/**
 * Status Command
 *
 * Returns the status of the bartender. If the bartender
 * is busy executing a command, the response will be
 * RSP_BUSY but if the bartender is not executing a command
 * RSP_WAITING is returned
 */
#define CMD_STATUS 0x04

/**
 * The response to the status command. Contains the current status of the
 * bartender.
 */
#define RES_STATUS_STATUS 0x04

/**
 * Location Command
 *
 * Returns the current location of bartender
 */
#define CMD_LOCATION 0x05

// --------------------------------------------------------
// Response Section
// --------------------------------------------------------

/**
 * Location of the response code
 */
#define I_RSP_CODE 0x03

/**
 * We have received the command and it is of valid syntax
 */
#define RSP_OK 0x01

/**
 * We have completed the command
 */
#define RSP_COMPLETE 0x05

/**
 * An general error response. Try to avoid this code and use a more useful code.
 */
#define RSP_ERROR 0x02

/**
 * Malformed message error. Sent when a message is received that does not have the
 * start and stop byte.
 */
#define RSP_MAL_MSG 0x03

/**
 * Unknown command error. Send when a message is received with a command code that is not
 * recognized by the handler.
 */
#define RSP_UNK_CMD 0x04

/**
 * Unknown type error. Sent when a message is received with response code that is not defined
 * by the protocol.
 */
#define RSP_UNK_TYPE 0x06

/**
 * Not implemented error. Sent when a message is received that is defined by the protocol but
 * the command can not be executed due to lack of implementation. Mostly used when debugging however
 * this code is useful if new versions of the protocol arise.
 */
#define RSP_NOT_IMPL 0x07

/**
 * Fatal error code. This means that a fatal error occurred and the device's state is no longer known.
 * Basically if this error code is received the device can not be counted on to do normal operation and
 * should be reset.
 */
#define RSP_FATAL_ERROR 0x08

/**
 * Queue full response. Send when a message would overflow the message queue. This means that the message
 * has been ignored.
 */
#define RSP_QUEUE_FULL 0x09

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name    Protocol Build Error Response
 * @brief   Build a protocol error response
 * @ingroup protocol
 *
 * This function build a protocol error response in the passed in parameter of buffer.
 *
 * @param [out] buffer a buffer that is of length MSG_SIZE that the error response will be
 * written to
 * @param [in] cmd the command code that the error is responding to
 * @param [in] code the error response code that the message should contain
 *
 */
void protocol_build_error_rsp(uint8_t *buffer, uint8_t cmd, uint8_t code);

/**
 * @name    Protocol Build Ok Response
 * @brief   Build a protocol ok response
 * @ingroup protocol
 *
 * This function build a protocol ok response in the passed in parameter of buffer.
 *
 * @param [out] buffer a buffer that is of length MSG_SIZE that the response will be
 * written to
 * @param [in] cmd the command code that the message is responding to
 *
 */
void protocol_build_ok_rsp(uint8_t *buffer, uint8_t cmd);

/**
 * @name    Protocol Build Complete Response
 * @brief   Build a protocol complete response
 * @ingroup protocol
 *
 * This function build a protocol complete response in the passed in parameter of buffer.
 *
 * @param [out] buffer a buffer that is of length MSG_SIZE that the response will be
 * written to
 * @param [in] cmd the command code that the message is responding to
 *
 */
void protocol_build_complete_rsp(uint8_t *buffer, uint8_t cmd);

#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_H_ */
