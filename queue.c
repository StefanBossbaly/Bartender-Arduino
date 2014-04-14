#include "queue.h"
#include "error.h"

void queue_init(queue_t *queue, uint8_t *data, uint8_t data_size, uint8_t capacity)
{
	queue->data = data;
	queue->data_size = data_size;

	queue->capacity = capacity;
	queue->size = 0;

	queue->head = 0;
	queue->tail = 0;
}

uint8_t queue_enqueue(queue_t *queue, const uint8_t *data)
{
	// Check to make sure that we do not overflow
	if (queue->size + 1 > queue->capacity)
	{
		return E_BUFF_OVERFLOW;
	}

	// Get the starting index
	uint16_t realIndex = queue->head * queue->data_size;

	// Iterate the input buffer
	for (uint8_t i = 0; i < queue->data_size; i++)
	{
		queue->data[realIndex] = data[i];
		realIndex++;
	}

	// Calculate the new head
	queue->head = (queue->head + 1) % queue->capacity;
	queue->size++;

	return E_NO_ERROR;
}

uint8_t queue_dequeue(queue_t *queue, uint8_t *data)
{
	// Make sure there is something to dequeue
	if (queue->size == 0)
	{
		return E_EMPTY;
	}

	// Get the starting index
	uint16_t realIndex = queue->tail * queue->data_size;

	// Iterate the input buffer
	for (uint8_t i = 0; i < queue->data_size; i++)
	{
		data[i] = queue->data[realIndex];
		realIndex++;
	}

	// Calculate the new tail
	queue->tail = (queue->tail + 1) % queue->capacity;
	queue->size--;

	return E_NO_ERROR;
}
