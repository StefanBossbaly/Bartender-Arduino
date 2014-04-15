#ifndef BAUD_TOL
#define BAUD_TOL 2
#endif

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "error.h"

typedef struct {
	uint8_t buffer[USART_RX_BUFFER_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
} rx_buffer;

typedef struct {
	uint8_t buffer[USART_TX_BUFFER_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
} tx_buffer;

tx_buffer tx_buff;
rx_buffer rx_buff;

static uint8_t tx_store_byte(uint8_t byte)
{
	uint8_t head = (uint8_t) ((tx_buff.head + 1) % USART_TX_BUFFER_SIZE);

	// Make sure that we have space
	if (head != tx_buff.tail)
	{
		tx_buff.buffer[tx_buff.head] = byte;
		tx_buff.head = head;

		return E_NO_ERROR;
	}

	return E_BUFF_OVERFLOW;
}

static uint8_t tx_read_byte(uint8_t *data_out)
{
	if (tx_buff.head != tx_buff.tail)
	{
		uint8_t data = tx_buff.buffer[tx_buff.tail];
		tx_buff.tail = (uint8_t) ((tx_buff.tail + 1) % USART_TX_BUFFER_SIZE);

		*data_out = data;

		return E_NO_ERROR;
	}

	return E_EMPTY;
}

static uint8_t rx_store_byte(uint8_t byte)
{
	uint8_t head = (uint8_t) ((rx_buff.head + 1) % USART_RX_BUFFER_SIZE);

	// Make sure that we have space
	if (head != rx_buff.tail)
	{
		rx_buff.buffer[rx_buff.head] = byte;
		rx_buff.head = head;

		return E_NO_ERROR;
	}

	return E_BUFF_OVERFLOW;
}

static uint8_t rx_read_byte(uint8_t *data_out)
{
	if (rx_buff.head != rx_buff.tail)
	{
		uint8_t data = rx_buff.buffer[rx_buff.tail];
		rx_buff.tail = (uint8_t) ((rx_buff.tail + 1) % USART_RX_BUFFER_SIZE);

		*data_out = data;
		return E_NO_ERROR;
	}

	return E_EMPTY;
}

void serial_begin(unsigned long baud)
{
	rx_buff.head = rx_buff.tail = 0;
	tx_buff.head = tx_buff.tail = 0;

	// Page 179 of documentation
    uint8_t use2x = 0;
    uint16_t ubbr = (F_CPU + 8UL * baud) / (16UL * baud) - 1UL;
    if ((100 * (F_CPU)) > (16 * (ubbr + 1) * (100 * ubbr + ubbr * BAUD_TOL)))
    {
        use2x = 1;
        ubbr = (F_CPU + 4UL * baud) / (8UL * baud) - 1UL;
    }

	// Set the upper and lower bits of the
	// baud rate
	UBRR0H = (uint8_t) (ubbr >> 8);
	UBRR0L = (uint8_t) ubbr;

	// UCSRnA Register
	// Page 195 of documentation
    if (use2x) {
        UCSR0A |= (1 << U2X0);
    } else {
        UCSR0A &= ~(1 << U2X0);
    }

    // UCSRnB Register
    // Page 196 of documentation
	// Let's fire up the circuit

    // Enable Transmitter and Enable Receiver
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

	// Enable Rx Complete Interrupt
	UCSR0B |= (1 << RXCIE0);
}

uint8_t serial_read_byte(uint8_t *data_out)
{
	uint8_t data, status;

	status = rx_read_byte(&data);

	*data_out = data;

	return status;
}

uint8_t serial_available()
{
	return (uint8_t) (USART_RX_BUFFER_SIZE + rx_buff.head - rx_buff.tail) % USART_RX_BUFFER_SIZE;
}

uint8_t serial_write_byte(uint8_t data)
{
	uint8_t status;

	// Store the byte in our buffer
	status = tx_store_byte(data);

	// Enable Data Register Empty interrupt
	UCSR0B |= (1 << UDRIE0);

	return status;
}

uint8_t serial_write_chunk(void *data, uint8_t size)
{
	uint8_t status;
	uint8_t *ptr = (uint8_t *) data;

	for (uint8_t i = 0; i < size; i++)
	{
		if ((status = serial_write_byte(*(ptr + i))) != E_NO_ERROR)
		{
			return status;
		}
	}

	return E_NO_ERROR;
}

/**
 * Recieve handler
 */
ISR (USART_RX_vect)
{
	// Get the data
	uint8_t data = UDR0;

	rx_store_byte(data);
}

/*
 * Transmit Data Empty
 */
ISR (USART_UDRE_vect)
{
	// We don't have any more data
	// so disable the interrupt
	if (tx_buff.head == tx_buff.tail)
	{
		UCSR0B &= ~(1 << UDRIE0);
	}
	// Put the next byte into the tx register
	else
	{
		uint8_t data;
		tx_read_byte(&data);
		UDR0 = data;

	}
}
