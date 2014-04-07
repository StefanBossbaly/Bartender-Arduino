#include "stepper.h"
#include "protocol.h"
#include "inttypes.h"
#include "serial.h"
#include "handler.h"
#include "bartender.h"
#include "timer.h"

stepper_t stepper;
handler_t handler;
toggle_driver_t toggler;
bartender_t bartender;

// Current buffers
uint8_t command[MSG_SIZE];
uint8_t response[MSG_SIZE];

uint8_t status = 0;
uint8_t size = 0;

void handle()
{
	
}

void setup()
{
	// Move this somewhere else
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	
	// Begin serial command
	serial_begin(9600);
	
	// Init stepper
	stepper_init(&stepper, 2, 3, 4, 5);
	stepper.delay = 3;
	stepper_release(&stepper);
	
	// Init Toggler
	toggle_driver_init(&toggler, 7, 8);
	
	// Init bartender
	bartender_init(&bartender, &stepper, &toggler, 0);
	
	// Init message handler
	handler_init(&handler, &bartender);
	
	// Init the timer
	timer2_init_ms(150, handle);
}

void loop()
{
	while (serial_available() > 0)
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
	
	delay(5);
}