#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "inttypes.h"


#define MSG_SIZE 32

// Header Section

#define I_TYPE 0x01

#define TYPE_CMD 0x02
#define TYPE_RSP 0x01



#define I_START 0x00
#define I_END 0x1F

#define MSG_START 0xFF
#define MSG_END 0xFE



// --------------------------------------------------------
// Command Section
// --------------------------------------------------------

#define BLANK 0x00

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

#define PARAM_LOC 0x04

/**
 * Pour Command <amount>
 *
 * Tells the bartender to pour an amount from the
 * current location
 */
#define CMD_POUR 0x03

/**
 * Status Command
 *
 * Returns the status of the bartender. If the bartender
 * is busy executing a command, the response will be
 * RSP_BUSY but if the bartender is not executing a command
 * RSP_WAITING is returned
 */
#define CMD_STATUS 0x04

#define PARAM_STATUS 0x04

/**
 * Location Command
 *
 * Returns the current location of bartender
 */
#define CMD_LOCATION 0x05

/**
 *
 */

// --------------------------------------------------------
// Response Section
// --------------------------------------------------------

#define I_RSP_CODE 0x03

/**
 * Response is
 */
#define RSP_OK 0x01

/**
 * An general error response. Try to avoid
 * this code and user a more useful code.
 */
#define RSP_ERROR 0x02

/**
 * Malformed message error. Sent when a message
 * is received that does not have the start and stop
 * byte.
 */
#define RSP_MAL_MSG 0x03

/**
 * Unknown command error. Send when a message
 * is received with a command code that is not
 * recognized by the handler.
 */
#define RSP_UNK_CMD 0x04

#ifdef __cplusplus
extern "C"
{
#endif

void protocol_build_error_rsp(uint8_t *buffer, uint8_t cmd, uint8_t code);
void protocol_build_ok_rsp(uint8_t *buffer, uint8_t cmd);

#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_H_ */
