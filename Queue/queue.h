
/**
 * @file queue.h
 * @author Juan Manuel Torres Palma
 * @brief Generic C queue declaration file
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h> // For size_t

/*
 * @brief A generic queue struct using arrays as containers.
 * @var data Array where data will be stored. Declared as void * to be
 * generic.
 * @var head Index to the first data introduced.
 * @var tail Index where next data should be introduced.
 * @var el_size Size of each element in the queue. Should be constant.
 * @var max_size Maximum size of elements in the queue.
 * @var size Current size of the queue.
 */
typedef struct queue{
	void *data;				/* Actual data, generic */
	size_t el_size;			/* Element size. Should be constant */
	unsigned int max_size;	/* Number of elements allocated in data */
	unsigned int size;		/* Number of inserted elements in data. */
	unsigned int head;		/* Pointer to next data to be returned */
	unsigned int tail;		/* Pointer to last data inserted */
} queue_t; 

/*
 * @brief Initialize a new queue.
 * @param [in] my_q Pointer to the queue to be initialized.
 * @param [in] size Size in bytes of a single element.
 * @code
 * 		queue_init(&s, sizeof(int));
 * @endcode 
 */
void queue_init(queue_t *const my_q, size_t size);
 
/*
 * @brief Destroy the queue and free its resources.
 * @param my_queue Pointer to the queue to be freed up.
 */
void queue_destroy(queue_t *const my_queue);

/*
 * @brief Adds a new element to the queue.
 * @param [in] my_queue Pointer to the queue where will add the item.
 * @param [in] item Pointer to the item to be attached.
 */
void queue_push_back(queue_t *const my_queue, void *item);

/*
 * @brief Returns the top element of the queue and deletes it.
 * @param [in] my_queue Pointer to the queue to be popped.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_queue.
 */
unsigned int queue_pop_front(queue_t *const my_queue, void *item);

/*
 * @brief Gets the oldest element in the queue.
 * @param [in] my_queue Pointer to the queue to be checked.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_queue.
 */
unsigned int queue_front(queue_t *const my_queue, void *item);

/*
 * @brief Gets the oldest element in the queue.
 * @param [in] my_queue Pointer to the queue to be checked.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_queue.
 */
unsigned int queue_back(queue_t *const my_queue, void *item);

/*
 * @brief Checks if the queue is full.
 * @param [in] my_queue Pointer to the queue to be checked.
 * @return State of the queue.
 * @retval 1 Full queue.
 * @retval 0 Not full queue.
 */
inline unsigned char queue_full(queue_t *const my_q);

/*
 * @brief Checks if the queue is empty.
 * @param [in] my_queue Pointer to the queue to be checked.
 * @return State of the queue.
 * @retval 1 Empty queue.
 * @retval 0 Not empty queue.
 */
inline unsigned char queue_empty(queue_t *const my_q);

/*
 * @brief Returns the number of allocated items.
 * @param [in] my_queue Pointer to the queue to be checked.
 * @return Number of items in the queue.
 */
inline unsigned int queue_size(queue_t *const my_q);

#endif /* QUEUE_H_ */
