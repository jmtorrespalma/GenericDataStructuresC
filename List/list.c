#include <stdlib.h> /* For malloc and free */
#include <string.h> /* For memcpy */
#include "list.h"


/*
 * @brief Internal node struct used in double linked list.
 * @var next Pointer to the next node in the list.
 * @var prev Pointer to the previous node.
 * @var data Pointer to the stored value.
 */
typedef struct list_node{
	struct list_node *next;
	struct list_node *prev;
	void *data;
} list_node_t;


/**
 * @brief Function to easily create new nodes.
 * @var prev Pointer to the previous node.
 * @var next Pointer to the next node.
 * @var data_s Size of data field.
 * @var item Pointer to item to be copied.
 * @return Pointer to the new node.
 */
static inline list_node_t *list_node_create(list_node_t *const prev,
				list_node_t *const next, size_t data_s, void *item){
	
	list_node_t *temp_ptr = malloc(sizeof(list_node_t));

	temp_ptr->next = next; /* Chained to the next node */
	temp_ptr->prev = prev; /* Chained to the previous node */
	temp_ptr->data = malloc(data_s);
	memcpy(temp_ptr->data, item, data_s); /* Assign data */


	return temp_ptr;

}


/* ************************************************** */

void list_init(list_t *const my_l, size_t size)
{

	my_l->el_size = size; 			 // Data size
	my_l->size = 0; 				 // Zero elements initially.	

	my_l->tail = NULL; //First place to add data.
	my_l->head = NULL;
}

/* ************************************************** */
/**
 * Starts destroying from head to the last node.
 */
void list_destroy(list_t *const my_list)
{
	/* Stores pointer to node to remove */
	list_node_t *dptr = my_list->head;
	/* Stores pointer to next node to remove */
	list_node_t *ndptr;

	while(dptr != NULL){ /* The last node next pointer is NULL */
		ndptr = dptr->next;
		free(dptr->data); /* Free data */
		free(dptr);	/* Free node */
		dptr = ndptr;
	}

}

/* ************************************************** */
/**
 * We can always push elements into the list.
 */
void list_push_back(list_t *const my_list, void *item)
{
	/* List tail */
	list_node_t *tail = my_list->tail;
	/* Create new node */
	list_node_t *temp_ptr = list_node_create(tail, NULL, my_list->el_size,
												item);


	/* At this point the new node is complete */

	/* Update previous last node, pointing to new last node */
	/* If there's no previous node, this one is the first */
	if (tail != NULL){ /* If there was a node before */
		tail->next = temp_ptr;
	} else { /* If it's the first node */
		my_list->head = temp_ptr;
	}

	/* Increase size */
	++(my_list->size);

	/* Update tail */
	my_list->tail = temp_ptr;


}

/* ************************************************** */
/**
 * Deletes the node at the end of the list and links
 * the tail of the list.
 */
unsigned int list_pop_back(list_t *const my_list, void *item)
{
	
	if (list_empty(my_list)){
		return 0;
	}

	/* Needed to dereference list tail */
	list_node_t *tail = my_list->tail;	

	/* Make new last node */
	my_list->tail = tail->prev;
	if (tail->prev != NULL){ /* If not last node */
		tail->prev->next = NULL;
	} else {
		my_list->head = NULL;
	}

	/* Copy data */
	if (item != NULL){
		memcpy(item, tail->data, my_list->el_size);
	}

	/* Delete node*/
	free(tail->data);
	free(tail);

	return --my_list->size;

}

/* ************************************************** */

void list_push_front(list_t *const my_list, void *item){
	
	/* List head */
	list_node_t *head = my_list->head;
	/* Create new node */
	list_node_t *temp_ptr = list_node_create(NULL, head, my_list->el_size,
												item);
	
		
	/* At this point the new node is complete */

	/* Update previous first node, pointing to new first node */
	/* If there's no previous first node, it's the only node */
	if (head != NULL){ /* If not first node that we create */
		head->prev = temp_ptr;
	} else {
		my_list->tail = temp_ptr;
	}

	/* Increase size */
	++(my_list->size);

	/* Update tail */
	my_list->head = temp_ptr;


}


/* ************************************************** */

unsigned int list_pop_front(list_t *const my_list, void *item){

	if (list_empty(my_list)){
		return 0;
	}

	/* Needed to dereference list head */
	list_node_t *head = my_list->head;	

	/* Make new first node */
	my_list->head = head->next;
	if (head->next != NULL){ /* If no the only node */
		head->next->prev = NULL;
	} else { /* List will be empty */
		my_list->tail = NULL;
	}

	/* Copy data */
	if (item != NULL){
		memcpy(item, head->data, my_list->el_size);
	}

	/* Delete node*/
	free(head->data);
	free(head);

	return --my_list->size;

}

/* ************************************************** */

unsigned int list_front(list_t *const my_l, void *item){

	list_node_t *head = my_l->head;

	if (list_empty(my_l)){
		return 0;
	}

	memcpy(item, head->data, my_l->el_size);
	return my_l->size;
	
}

/* ************************************************** */

unsigned int list_back(list_t *const my_l, void *item){

	list_node_t *tail = my_l->tail;

	if (list_empty(my_l)){
		return 0;
	}

	memcpy(item, tail->data, my_l->el_size);
	return my_l->size;
	
}

/* ************************************************** */


/* ************************************************** */


/* ************************************************** */



