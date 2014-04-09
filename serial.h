#ifndef SERIAL_H_
#define SERIAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>

#define USART_RX_BUFFER_SIZE 64
#define USART_TX_BUFFER_SIZE 64

#define E_NO_ERROR 0x00
#define E_GENERAL 0x01
#define E_BUFF_OVERFLOW 0x02
#define E_EMPTY 0x03

void serial_begin(unsigned long baud);
uint8_t serial_read_byte(uint8_t *data_out);
uint8_t serial_available();
uint8_t serial_write_byte(uint8_t data);
uint8_t serial_write_chunk(void *data, uint8_t size);


#ifdef __cplusplus
}
#endif

#endif /* SERIAL_H_ */
