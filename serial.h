/*
 * serial.h
 *
 *  Created on: Mar 11, 2014
 *      Author: stefan
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>


#define USART_RX_BUFFER_SIZE 16
#define USART_TX_BUFFER_SIZE 32

void serial_begin(unsigned long baud);
uint8_t serial_read_byte();
uint8_t serial_available();
void serial_write_byte(uint8_t data);


#ifdef __cplusplus
}
#endif

#endif /* SERIAL_H_ */
