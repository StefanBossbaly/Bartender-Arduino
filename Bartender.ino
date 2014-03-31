#include "stepper.h"
#include "protocol.h"
#include "inttypes.h"
#include "serial.h"
#include "handler.h"

stepper_t stepper;
handler_t handler;
uint8_t command[MSG_SIZE];
uint8_t response[MSG_SIZE];
int size = 0;

void setup()
{
	serial_begin(9600);
	handler_init(&handler, &stepper);
}


void loop()
{
	if (serial_available() > 0)
	{
		serial_read_byte(&command[size]);
		size++;
	}
	
	if (size == 32)
	{
		handler_handle(&handler, command, response);
		serial_write_chunk(response, MSG_SIZE);
		size = 0;
	}
	
	delay(10);
}