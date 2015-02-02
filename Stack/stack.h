
/**
 * @file stack.h
 * @author Juan Manuel Torres Palma
 * @brief Generic C stack declaration file
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h> // For size_t


/*
 * @brief A generic stack struct using arrays as containers to maximize.
 * @var data Array where data will be stored. Declared as void * to be
 * generic.
 * @var el_size Size of each element in the stack. Should be constant.
 * @var max_size Maximum size of elements in the stack.
 * @var size Current size of the stack.
 */
typedef struct stack{
	void *data;				/* Actual data, generic */
	size_t el_size;			/* Element size. Should be constant */
	unsigned int max_size;	/* Number of elements allocated in data */
	unsigned int size;		/* Number of inserted elements in data. Real data */
} stack_t; 

/*
 * @brief Initialize a new stack.
 * @param [in] my_s Pointer to the stack to be initialized.
 * @param [in] size Size in bytes of a single element.
 * @code
 * 		stack_init(&s, sizeof(int));
 * @endcode 
 */
void stack_init(stack_t *const my_s, size_t size);
 
/*
 * @brief Destroy the stack and free its resources.
 * @param my_stack Pointer to the stack to be freed up.
 */
void stack_destroy(stack_t *const my_stack);

/*
 * @brief Adds a new element to the stack.
 * @param [in] my_stack Pointer to the stack where will add the item.
 * @param [in] item Pointer to the item to be attached.
 */
void stack_push(stack_t *const my_stack, void *item);

/*
 * @brief Returns the top element of the stack and deletes it.
 * @param [in] my_stack Pointer to the stack to be popped.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_stack.
 */
unsigned int stack_pop(stack_t *const my_stack, void *item);

/*
 * @brief Gets the last element added.
 * @param [in] my_stack Pointer to the stack to be checked.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_stack.
 */
unsigned int stack_top(stack_t *const my_stack, void *item);

/*
 * @brief Checks if the stack is full.
 * @param [in] my_stack Pointer to the stack to be checked.
 * @return State of the stack.
 * @retval 1 Full stack.
 * @retval 0 Not full stack.
 */
inline unsigned char stack_full(stack_t *const my_s);

/*
 * @brief Checks if the stack is empty.
 * @param [in] my_stack Pointer to the stack to be checked.
 * @return State of the stack.
 * @retval 1 Empty stack.
 * @retval 0 Not empty stack.
 */
inline unsigned char stack_empty(stack_t *const my_s);

/*
 * @brief Returns the number of allocated items.
 * @param [in] my_stack Pointer to the stack to be checked.
 * @return Number of items in the stack.
 */
inline unsigned int stack_size(stack_t *const my_s);

#endif /* STACK_H_ */
