/**
 * @file   queue.h
 * @brief  Defines a queue that holds a fixed size data type
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 * These queue functions are implemented using a ring buffer. The buffer has a
 * head which is where the the next element is inserted. It also has a tail which
 * is the position where the next element to be dequeued is stored.
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>

/**
 * A structure that represents a queue that uses a ring buffer to hold its
 * data elements.
 */
typedef struct
{
	uint8_t *data; /**< the buffer used to store data elements */
	uint8_t data_size; /**< the size of the data elements */

	uint8_t capacity; /**< the number of data elements the buffer can hold  */
	uint8_t size; /**< the number of data elements currently in the queue */

	uint8_t head; /**< the index of the first element in the queue */
	uint8_t tail; /**< the index of the last element in the queue  */
} queue_t;

/**
 * @name    Initialize the Queue
 * @brief   Sets up the default values for the queue structure.
 * @ingroup queue
 *
 * Sets up a queue_t.
 *
 * @param [in] queue the queue that will be initialized
 * @param [in] data the buffer used to store the values of the queue
 * @param [in] data_size the fixed size in bytes of the elements of the queue
 * @param [in] capacity how many data elements the buffer can hold
 *
 */
void queue_init(queue_t *queue, uint8_t *data, uint8_t data_size, uint8_t capacity);

/**
 * @name    Enqueue an Item
 * @brief   Adds an data element to the queue.
 * @ingroup queue
 *
 * Adds an element to the back of the queue.
 *
 * @warning This function returns E_BUFF_OVERFLOW if adding another
 * element to the queue exceeds the buffer capacity.
 *
 * @param [in] queue the queue that the element will be added to
 * @param [in] data the data element that will be added to the queue
 *
 * @retval E_NO_ERROR if no error occurred and the item was successfully added.
 * @retval E_BUFF_OVERFLOW if adding another element would exceed the queue's
 * capacity
 *
 */
uint8_t queue_enqueue(queue_t *queue, const uint8_t *data);

/**
 * @name    Dequeue an Item
 * @brief   Removes an data element to the queue.
 * @ingroup queue
 *
 * Removes the first element in the queue.
 *
 * @warning This function returns E_EMPTY if the queue is empty.
 *
 * @param [in] queue the queue that the element will be added to
 * @param [out] data the buffer where the removed item will be copied to.
 *
 * @retval E_NO_ERROR if no error occurred and the item was successfully removed.
 * @retval E_EMPTY if the queue is empty
 *
 */
uint8_t queue_dequeue(queue_t *queue, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H_ */
