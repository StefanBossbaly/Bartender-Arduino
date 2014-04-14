#include "stepper.h"
#include "protocol.h"
#include "inttypes.h"
#include "serial.h"
#include "handler.h"
#include "bartender.h"
#include "timer.h"
#include "queue.h"
#include "error.h"

stepper_t stepper;
handler_t handler;
toggle_driver_t toggler;
bartender_t bartender;

// Data for the queue
queue_t queue;
uint8_t qdata[MSG_SIZE * 10];

// Current buffers
uint8_t temp_buffer[MSG_SIZE];
uint8_t size = 0;

void handle()
{
	// While there is serial data available
	while (serial_available() > 0)
	{
		// Copy the byte into our temp buffer
		serial_read_byte(&temp_buffer[size]);
		size++;
		
		// We have a message! I wonder who its from
		if (size == MSG_SIZE)
		{
			// If it is the status or the stop command we need to process it right away
			if (temp_buffer[I_CMD] == CMD_STATUS || temp_buffer[I_CMD] == CMD_STOP)
			{
				handler_handle(&handler, temp_buffer);
			}
			else
			{
				// Add the buffer to the queue
				uint8_t error = queue_enqueue(&queue, temp_buffer);
				
				// Oh boy a fatal error
				if (error != E_NO_ERROR)
				{
					
				}
			}
			
			// Clear the buffer
			size = 0;
		}
	}
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
	queue_init(&queue, qdata, MSG_SIZE, 10);
	
	// Init the timer
	timer2_init_ms(150, handle);
}

void loop()
{
	// If we have commands to process
	if (queue.size != 0)
	{
		// Declare temporary storage for the command
		uint8_t cmd[MSG_SIZE];
		
		// Dequeue the next command in the queue
		queue_dequeue(&queue, cmd);
		
		// Handle the next command
		handler_handle(&handler, cmd);
	}
	
	// Sleep little baby
	delay(5);
}