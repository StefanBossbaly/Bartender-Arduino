#include <Arduino.h>

#include "handler.h"
#include "protocol.h"
#include "serial.h"

static void handler_process_cmd_stop(handler_t *handler, uint8_t *buffer, uint8_t *rsp);
static void handler_process_cmd_move(handler_t *handler, uint8_t *buffer, uint8_t *rsp);
static void handler_process_cmd_pour(handler_t *handler, uint8_t *buffer, uint8_t *rsp);
static void handler_process_cmd_status(handler_t *handler, uint8_t *buffer, uint8_t *rsp);
static void handler_process_cmd_location(handler_t *handler, uint8_t *buffer, uint8_t *rsp);
static void handler_process_unknown_cmd(handler_t *handler, uint8_t *buffer, uint8_t *rsp);

void handler_init(handler_t *handler, bartender_t *bartender)
{
	handler->bartender = bartender;
}

void handler_handle(handler_t *handler, uint8_t *cmd)
{
	uint8_t rsp[MSG_SIZE];

	// Make sure we have a valid packet
	if (cmd[I_START] != MSG_START || cmd[I_END] != MSG_END)
	{
		// Send back a malformed packet error
		protocol_build_error_rsp(rsp, BLANK, RSP_MAL_MSG);
		serial_write_chunk(rsp, MSG_SIZE);
		return;
	}

	// See if the type is command
	if (cmd[I_TYPE] == TYPE_CMD)
	{
		// Find the function to handle the command
		switch(cmd[I_CMD])
		{
		case CMD_STOP:
			handler_process_cmd_stop(handler, cmd, rsp);
			break;
		case CMD_MOVE:
			handler_process_cmd_move(handler, cmd, rsp);
			break;
		case CMD_POUR:
			handler_process_cmd_pour(handler, cmd, rsp);
			break;
		case CMD_STATUS:
			handler_process_cmd_status(handler, cmd, rsp);
			break;
		case CMD_LOCATION:
			handler_process_cmd_location(handler, cmd, rsp);
			break;
		default:
			handler_process_unknown_cmd(handler, cmd, rsp);
			break;
		}
	}
	else if (cmd[I_TYPE] == TYPE_RSP)
	{
		// Send back a not implemented type error
		protocol_build_error_rsp(rsp, BLANK, RSP_NOT_IMPL);
		serial_write_chunk(rsp, MSG_SIZE);
	}
	else
	{
		// Send back an unknown type error
		protocol_build_error_rsp(rsp, BLANK, RSP_UNK_TYPE);
		serial_write_chunk(rsp, MSG_SIZE);
	}
}

static void handler_process_cmd_stop(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	protocol_build_ok_rsp(rsp, CMD_STOP);
}

static void handler_process_cmd_move(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	//Grab the variables from the content
	uint8_t location = buffer[PARAM_MOVE_LOC];

	// Make sure the location is in range
	if (location > 12)
	{
		// Let them know we are not happy
		protocol_build_error_rsp(rsp, CMD_MOVE, RSP_ERROR);
		serial_write_chunk(rsp, MSG_SIZE);
		return;
	}

	// We are processing the command
	protocol_build_ok_rsp(rsp, CMD_MOVE);
	serial_write_chunk(rsp, MSG_SIZE);

	// Start moving
	uint8_t code = bartender_move_to_location(handler->bartender, location);

	if (code == E_NO_ERROR)
	{
		// We have processed the command
		protocol_build_complete_rsp(rsp, CMD_MOVE);
		serial_write_chunk(rsp, MSG_SIZE);
	}
	else
	{
		// TODO better error code
		protocol_build_error_rsp(rsp, CMD_MOVE, RSP_ERROR);
		serial_write_chunk(rsp, MSG_SIZE);
	}
}

static void handler_process_cmd_pour(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	// We have received the command
	protocol_build_ok_rsp(rsp, CMD_POUR);
	serial_write_chunk(rsp, MSG_SIZE);

	uint8_t amount = rsp[PARAM_POUR_AMOUNT];

	uint8_t code = bartender_pour(handler->bartender, amount);

	if (code == E_NO_ERROR)
	{
		// The command has been completed
		protocol_build_complete_rsp(rsp, CMD_POUR);
		serial_write_chunk(rsp, MSG_SIZE);
	}
	else
	{
		//TODO better error codes
		protocol_build_error_rsp(rsp, CMD_MOVE, RSP_ERROR);
		serial_write_chunk(rsp, MSG_SIZE);
	}
}

static void handler_process_cmd_status(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	// Build a response
	protocol_build_ok_rsp(rsp, CMD_STATUS);

	// Put in the bartender's current status
	rsp[RES_STATUS_STATUS] = handler->bartender->status;

	// Write the command back
	serial_write_chunk(rsp, MSG_SIZE);
}

static void handler_process_cmd_location(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	protocol_build_ok_rsp(rsp, CMD_LOCATION);
}

static void handler_process_unknown_cmd(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	protocol_build_error_rsp(rsp, BLANK, RSP_UNK_CMD);
}

