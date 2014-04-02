/*
 * handler.c
 *
 *  Created on: Mar 30, 2014
 *      Author: stefan
 */

#include "handler.h"
#include "protocol.h"

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

void handler_handle(handler_t *handler, uint8_t *cmd, uint8_t *rsp)
{
	// Make sure we have a valid packet
	if (cmd[I_START] != MSG_START || cmd[I_END] != MSG_END)
	{
		// Send back a malformed packet error
		protocol_build_error_rsp(rsp, BLANK, RSP_MAL_MSG);
		return;
	}

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

static void handler_process_cmd_stop(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	protocol_build_ok_rsp(rsp, CMD_STOP);
}

static void handler_process_cmd_move(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	//Grab the variables from the content
	uint8_t location = buffer[PARAM_LOC];

	// Make sure the location is in range
	if (location > 12)
	{
		// Let them know we are not happy
		protocol_build_error_rsp(rsp, CMD_MOVE, RSP_ERROR);
		return;
	}

	// Start moving
	bartender_move_to_location(handler->bartender, location);

	// We have processed the command
	protocol_build_ok_rsp(rsp, CMD_MOVE);
}

static void handler_process_cmd_pour(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	protocol_build_ok_rsp(rsp, CMD_POUR);

	bartender_pour(handler->bartender, 0);
}

static void handler_process_cmd_status(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	// Build a response
	protocol_build_ok_rsp(rsp, CMD_POUR);

	// Put in the bartender's current status
	rsp[PARAM_STATUS] = handler->bartender->status;
}

static void handler_process_cmd_location(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	protocol_build_ok_rsp(rsp, CMD_LOCATION);
}

static void handler_process_unknown_cmd(handler_t *handler, uint8_t *buffer, uint8_t *rsp)
{
	protocol_build_error_rsp(rsp, BLANK, RSP_UNK_CMD);
}

