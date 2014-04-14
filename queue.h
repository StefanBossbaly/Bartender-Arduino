#ifndef QUEUE_H_
#define QUEUE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>

typedef struct
{
	uint8_t *data;
	uint8_t data_size;

	uint8_t capacity;
	uint8_t size;

	uint8_t head;
	uint8_t tail;
} queue_t;

void queue_init(queue_t *queue, uint8_t *data, uint8_t data_size, uint8_t capacity);
uint8_t queue_enqueue(queue_t *queue, const uint8_t *data);
uint8_t queue_dequeue(queue_t *queue, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H_ */
