#include "protocol.h"

static void protocol_clear_buffer(uint8_t *buffer);
static void protocol_add_endings(uint8_t *buffer);


static void protocol_add_endings(uint8_t *buffer)
{
	buffer[I_START] = MSG_START;
	buffer[I_END] = MSG_END;
}

static void protocol_clear_buffer(uint8_t *buffer)
{
	for (uint8_t i = 0; i < MSG_SIZE; i++)
	{
		buffer[i] = BLANK;
	}
}

void protocol_build_error_rsp(uint8_t *buffer, uint8_t cmd, uint8_t code)
{
	protocol_clear_buffer(buffer);
	protocol_add_endings(buffer);

	buffer[I_TYPE] = TYPE_RSP;
	buffer[I_CMD] = cmd;
	buffer[I_RSP_CODE] = code;
}

void protocol_build_ok_rsp(uint8_t *buffer, uint8_t cmd)
{
	protocol_clear_buffer(buffer);
	protocol_add_endings(buffer);

	buffer[I_TYPE] = TYPE_RSP;
	buffer[I_CMD] = cmd;
	buffer[I_RSP_CODE] = RSP_OK;
}


