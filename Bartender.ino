#include "stepper.h"
#include "protocol.h"
#include "inttypes.h"
#include "serial.h"

stepper_t stepper;

void setup()
{
	serial_begin(9600);
}


void loop()
{	
	
	char data[] = "ABC";
	
	serial_write_chunk(data, 3);
	//serial_write_byte(0x041);
	//serial_write_byte(0x0D);
	
	
	delay(1000);
}