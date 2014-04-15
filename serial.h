/**
 * @file   serial.h
 * @brief  Defines the functions that can be used for sending and receiving
 * data over a serial connection.
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 * The serial functions are used to transmit data over a serial connection. On
 * the UNO the serial pins are 0 and 1.
 */
#ifndef SERIAL_H_
#define SERIAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>
#include "error.h"

/**
 * The size of the receive buffer
 */
#define USART_RX_BUFFER_SIZE 64

/**
 * The size of the transmit buffer
 */
#define USART_TX_BUFFER_SIZE 64

/**
 * @name    Serial Begin
 * @brief	Starts and configures the serial chip
 * @ingroup serial
 *
 * This function begins a serial connection.
 *
 * @note This function must be called before calling the other serial functions.
 *
 * @param [in] baud the baud rate that the serial connection will communicate
 * over.
 */
void serial_begin(unsigned long baud);

/**
 * @name    Serial Read Byte
 * @brief	Reads the next byte in the serial RX queue
 * @ingroup serial
 *
 * This function reads the next byte in rx queue and then removes it from
 * the queue.
 *
 * @warning Returns E_EMPTY if the rx buffer is empty
 *
 * @param [out] data_out the address where the next byte in the buffer will
 * be stored
 *
 * @retval E_NO_ERROR no error occurred
 * @retval E_EMPTY the rx buffer is empty
 */
uint8_t serial_read_byte(uint8_t *data_out);

/**
 * @name    Serial Available
 * @brief	Sees how many bytes are currently available to be read
 * @ingroup serial
 *
 * This function sees how many bytes are currently available in the rx queue.
 *
 * @returns the number of bytes that can be read from the rx queue
 */
uint8_t serial_available();

/**
 * @name    Serial Write Byte
 * @brief	Enqueues a byte to be written on the serial connection
 * @ingroup serial
 *
 * This function enqueues the inputed byte to the tx buffer. Once all the bytes
 * before it are sent the inputed byte will then be sent.
 *
 * @warning Returns E_BUFF_OVERFLOW if the tx buffer is full prior to calling
 * this function
 *
 * @param [in] data the byte that will be enqueued on the tx queue
 *
 * @retval E_NO_ERROR no error occurred
 * @retval E_BUFF_OVERFLOW the tx buffer is full and adding the byte would overflow
 * it
 */
uint8_t serial_write_byte(uint8_t data);

/**
 * @name    Serial Write Chunk
 * @brief	Enqueues an array of bytes to the tx queue
 * @ingroup serial
 *
 * This function enqueues the array of bytes to the tx buffer. Once all the bytes
 * before it are sent the inputed array of bytes will then be sent.
 *
 * @warning Returns E_BUFF_OVERFLOW if the byte array would cause the tx buffer
 * to overflow. HOWEVER THE BYTES IN THE ARRAY BEFORE THE ARRAY WOULD HAVE OVERFLOWED
 * ARE STILL ADDED TO THE BUFFER.
 *
 * @warning Providing an incorrect parameter of size will cause a buffer overflow
 * that the serial functions can not detect.
 *
 * @param [in] data the byte array that will be enqueued on the tx queue
 * @param [in] size the size of the array
 *
 * @retval E_NO_ERROR no error occurred
 * @retval E_BUFF_OVERFLOW the tx buffer is full and adding the byte would overflow
 * it
 */
uint8_t serial_write_chunk(void *data, uint8_t size);


#ifdef __cplusplus
}
#endif

#endif /* SERIAL_H_ */
