#include "stepper.h"
#include "protocol.h"
#include "inttypes.h"
#include "serial.h"
#include "handler.h"
#include "bartender.h"
#include "timer.h"
#include "queue.h"

stepper_t stepper;
handler_t handler;
toggle_driver_t toggler;
bartender_t bartender;

queue_t queue;
uint8_t qdata[MSG_SIZE * 5];

// Current buffers
uint8_t command[MSG_SIZE];

uint8_t status = 0;
uint8_t size = 0;

void handle()
{
}

void setup()
{	
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
	
	// Init the queue
	queue_init(&queue, qdata, MSG_SIZE, 5);
	
	// Init the timer
	timer2_init_ms(100, handle);
}

void loop()
{
	// While there is data that needs to be read
	while (serial_available() > 0)
	{
		serial_read_byte(&command[size]);
		size++;
	}
	
	if (size == 32)
	{
		handler_handle(&handler, command);
		size = 0;
	}
}