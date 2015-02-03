#include "queue.h"
#include <stdlib.h> //For malloc and free
#include <string.h>  //For memcpy

#define DEFAULT_QUEUE_ELM 5  //Initial size of the data array

/**
 * @brief Macro to easily get the address from a queue index.
 * @param queue Pointer to the queue structure.
 * @param indx Index that we want to ge the address of.
 */
#define queue_calc_address(queue,indx)			\
	 queue->data + (queue->el_size * indx)
		



static unsigned char queue_resize(queue_t *my_q, unsigned int new_size);

/* ************************************************** */

void queue_init(queue_t *const my_q, size_t size){

	my_q->el_size = size; 			 // Data size
	my_q->max_size = DEFAULT_QUEUE_ELM;// Five spots
	my_q->size = 0; 				 // Zero elements initially.	

	my_q->data = malloc((size_t)size * my_q->max_size); //Allocate data
	my_q->tail = 0; //First place to add data.
	my_q->head = 0;
}

/* ************************************************** */

void queue_destroy(queue_t *const my_queue){
	free(my_queue->data);
}

/* ************************************************** */
/**
 * We can always push elements into the stack, cause in case it's full
 * it will be resized. 
 */
void queue_push_back(queue_t *const my_queue, void *item){
 
	/* If full, double the size */
	if (queue_full(my_queue)){
		queue_resize(my_queue, (my_queue->max_size)*2);
	}

	/* The position to append the new item is in tail */
	void *tail_address = queue_calc_address(my_queue, my_queue->tail);

 	/* Copy data into queue */	
	memcpy(tail_address, item, my_queue->el_size);

	/* Increase size */
	++(my_queue->size);

	/* Increase tail index */
	++(my_queue->tail);

	/* Check if it's in the last position */
	if (my_queue->tail == my_queue->max_size){
		/* Go back to beggining */
		my_queue->tail = 0;
	}

}

/* ************************************************** */

unsigned int queue_pop_front(queue_t *const my_queue, void *item){

	if (queue_empty(my_queue)){
		return 0;
	}

	/* The position where the last item is, is given by
 	   data_start + (size_of_element * head_of_queue)) */
	void *elem_pos = queue_calc_address(my_queue, my_queue->head);

	/* If the user wants to collect the value */
	if (item != NULL){
		memcpy(item, elem_pos, my_queue->el_size);
	}

	++my_queue->head;

	if (my_queue->head == my_queue->max_size){
		my_queue->head = 0;
	}
	
	return --my_queue->size;
	
}

/* ************************************************** */

unsigned int queue_front(queue_t *const my_q, void *item){

	if (queue_empty(my_q)){
		return 0;
	}

	/* The position where the first item is, is given by
 	   data_start + (size_of_element * head_of_queue)) */
	void *elem_pos = queue_calc_address(my_q, my_q->head);

	memcpy(item, elem_pos, my_q->el_size);
	return my_q->size;
	
}

/* ************************************************** */

unsigned int queue_back(queue_t *const my_q, void *item){

	unsigned last_el;

	if (queue_empty(my_q)){
		return 0;
	}

	/* Check if tail is at 0 to avoid overflow of integers */
	if (my_q->tail == 0){
		last_el = my_q->max_size;
	}
	else{
		last_el = my_q->tail - 1;
	}

	/* The position where the last item is, is given by
 	   data_start + (size_of_element * pos_of_last_element) */
	void *elem_pos = queue_calc_address(my_q, last_el);

	memcpy(item, elem_pos, my_q->el_size);
	return my_q->size;
	
}

/* ************************************************** */

inline unsigned char queue_full(queue_t *const my_q){
	return (my_q->max_size == my_q->size);
}

/* ************************************************** */

inline unsigned char queue_empty(queue_t *const my_q){
	return (my_q->size == 0);
}

/* ************************************************** */

inline unsigned int queue_size(queue_t *const my_q){
	return my_q->size;
}


/*
 * Private scope function
 * Returns a 0 if could resize it, or 1 if not
 */
static unsigned char queue_resize(queue_t *my_q, unsigned int new_size){
	void *new_data;		/* Pointer to store new data */
	void *freed_data; 	/* Aux pointer to swap and free old buffer */
	void *head_ptr;		/* Address of head */
	void *next_ptr;		/* Aux pointer detailed later */
	
	//Less elements than we currently have.
	if (new_size < my_q->size)
		return 1; 

	//Create new buffer
	new_data = malloc(my_q->el_size * new_size);


	/* Copy data. Needs to be done in various steps to keep
	 * the queue working
	 */
	head_ptr = queue_calc_address(my_q, my_q->head);

	/* If head is lower or equal to tail, only need one step copy */ 
	if (my_q->head < my_q->tail){
		memcpy(new_data, head_ptr, my_q->el_size * my_q->size);
	}
	/* In this case, we have to copy from head to end, and then
 	 * from beginning to end.
 	 */
 	else{
		/* Last position to copy */
		/* Blocks to copy until end of array */
		unsigned i_diff = my_q->max_size - my_q->head;
		memcpy(new_data, head_ptr, my_q->el_size * i_diff);
		
		/* Next no occupied address of new_data */
		next_ptr = new_data + (my_q->el_size * i_diff);	
		memcpy(next_ptr, my_q->data, my_q->el_size * my_q->tail);	
	}	 


	my_q->max_size = new_size;

	/* Point to first element, now at the beginning */
	my_q->head = 0;
	/* Point to last element + 1, now at the end */
	my_q->tail = my_q->size;

	//Assign new data block
	freed_data = my_q->data;
	my_q->data = new_data;
	
	//Free memory
	free(freed_data);
	
	return 0;
}
