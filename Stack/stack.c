#include "stack.h"
#include <stdlib.h> //For malloc and free
#include <string.h>  //For memcpy

#define DEFAULT_STACK_ELM 5


#define stack_calc_address(stack, indx) 		\
	stack->data + (stack->el_size * indx)

static unsigned char stack_resize(stack_t *my_s, unsigned int new_size);

/* ************************************************** */

void stack_init(stack_t *const my_s, size_t size){

	my_s->el_size = size; 			 // Data size
	my_s->max_size = DEFAULT_STACK_ELM;// Five spots
	my_s->size = 0; 				 // Zero elements initially.	

	my_s->data = malloc((size_t)size * my_s->max_size); //Create data array

}

/* ************************************************** */

void stack_destroy(stack_t *const my_stack){
	free(my_stack->data);
}

/* ************************************************** */

void stack_push(stack_t *const my_stack, void *item){
	/* The position to appent the new item is given by
 	   data_start + (size_of_element * number_of_elm_in_stack) */
 

	/* If full, double the size */
	if (stack_full(my_stack)){
		stack_resize(my_stack, (my_stack->max_size)*2);
	}

	void *cpy_start = stack_calc_address(my_stack, my_stack->size);

	
	memcpy(cpy_start, item, my_stack->el_size);
	++(my_stack->size);

}

/* ************************************************** */

unsigned int stack_pop(stack_t *const my_stack, void *item){

	if (stack_empty(my_stack)){
		return 0;
	}

	/* The position where the last item is, is given by
 	   data_start + (size_of_element * (number_of_elm_in_stack - 1)) */

	void *elem_pos = stack_calc_address(my_stack, my_stack->size - 1);

	memcpy(item, elem_pos, my_stack->el_size);
	return --(my_stack->size);
	
}

/* ************************************************** */

unsigned int stack_top(stack_t *const my_s, void *item){

	if (stack_empty(my_s)){
		return 0;
	}

	/* The position where the last item is, is given by
 	   data_start + (size_of_element * (number_of_elm_in_stack - 1)) */

	void *elem_pos = stack_calc_address(my_s, my_s->size - 1);

	memcpy(item, elem_pos, my_s->el_size);
	return my_s->size;
	
}

/* ************************************************** */

inline unsigned char stack_full(stack_t *const my_s){
	return (my_s->max_size == my_s->size);
}

/* ************************************************** */

inline unsigned char stack_empty(stack_t *const my_s){
	return (my_s->size == 0);
}

/* ************************************************** */

inline unsigned int stack_size(stack_t *const my_s){
	return my_s->size;
}


/*
 * Private scope function
 * Returns a 0 if could resize it, or 1 if not
 */
static unsigned char stack_resize(stack_t *my_s, unsigned int new_size){
	void *new_data, *freed_data;
	
	//Less elements than we currently have.
	if (new_size < my_s->size)
		return 1; 

	//Create new buffer
	new_data = malloc(my_s->el_size * new_size);
	//Copy data, doesnt check if overflows the reserved memory
	memcpy(new_data, my_s->data, my_s->el_size * my_s->size);

	//Assign new data block
	freed_data = my_s->data;
	my_s->data = new_data;
	
	//Free memory
	free(freed_data);
	
	return 0;
}
