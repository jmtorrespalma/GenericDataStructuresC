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



/* ************************************************** */
/**
 * @brief Macro to easily get the sentinel pointer dereferenced.
 * @param l List that we want to dereference.
 */
#define list_get_sent(l) ((list_node_t*) l->sent)

/* ************************************************** */
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

	/* Update nodes around */
	prev->next = temp_ptr; /* Previous points to current */
	next->prev = temp_ptr; /* Next points to current */
	

	return temp_ptr;

}

/* ************************************************** */
/**
 * @brief Function to easily destroy nodes. Links next and previous nodes,
 * so it's useful in almost all functions.
 * @var n_ptr Pointer to the node.
 */
static inline void list_node_destroy(list_node_t *const n_ptr)
{
	n_ptr->prev->next = n_ptr->next; /* Previous node points to next*/
	n_ptr->next->prev = n_ptr->prev; /* Next points to previous */
	free(n_ptr->data);
	free(n_ptr);
}

/* ************************************************** */

void list_init(list_t *const my_l, size_t size)
{
	list_node_t *sent = malloc(sizeof(list_node_t));
	sent->next = sent; /* Points to itself */
	sent->prev = sent;

	my_l->el_size = size; /* Data size */
	my_l->size = 0; 	  /* Zero elements initially */	
	my_l->sent = sent;    /* Sentinel */
}

/* ************************************************** */
/**
 * Starts destroying from head to the last node.
 */
void list_destroy(list_t *const my_list)
{
	/* Stores pointer to node to remove */
	list_node_t *dptr = list_get_sent(my_list)->next;
	/* Stores pointer to next node to remove */
	list_node_t *ndptr;
	/* Remove sentinel */
	free(my_list->sent);

	while (dptr != my_list->sent){
		ndptr = dptr->next; 	/* Save next pointer */
		free(dptr->data);		/* Destroy node */
		free(dptr);
		dptr = ndptr;			/* Point to next node */
	}

}

/* ************************************************** */
/**
 * We can always push elements into the list.
 */
void list_push_back(list_t *const my_list, void *item)
{
	/* List tail node*/
	list_node_t *tail = list_get_sent(my_list)->prev;
	/* Create new node and add it at the end */
	list_node_create(tail, my_list->sent, my_list->el_size, item);


	/* At this point the new node is complete, and those surrounding
 	   it too */

	/* Increase size */
	++(my_list->size);

}

/* ************************************************** */
/**
 * Deletes the node at the end of the list and links
 * the tail of the list.
 */
uint32_t list_pop_back(list_t *const my_list, void *item)
{
	
	if (list_empty(my_list)){
		return 0;
	}

	/* Needed to dereference list tail */
	list_node_t *tail = list_get_sent(my_list)->prev;	

	/* Copy data */
	if (item != NULL){
		memcpy(item, tail->data, my_list->el_size);
	}

	/* Delete node*/
	list_node_destroy(tail);

	return --my_list->size;

}

/* ************************************************** */

void list_push_front(list_t *const my_list, void *item)
{
	
	/* List head */
	list_node_t *head = list_get_sent(my_list)->next;
	/* Create new node */
	list_node_create(my_list->sent, head, my_list->el_size, item);
	
		
	/* At this point the new node is complete */

	/* Increase size */
	++(my_list->size);

}


/* ************************************************** */

uint32_t list_pop_front(list_t *const my_list, void *item)
{

	if (list_empty(my_list)){
		return 0;
	}

	/* Needed to dereference list head */
	list_node_t *head = list_get_sent(my_list)->next;	

	/* Copy data */
	if (item != NULL){
		memcpy(item, head->data, my_list->el_size);
	}

	/* Delete node*/
	list_node_destroy(head);

	return --my_list->size;

}

/* ************************************************** */

uint32_t list_front(list_t *const my_l, void *item)
{

	list_node_t *head = list_get_sent(my_l)->next;

	if (list_empty(my_l)){
		return 0;
	}

	memcpy(item, head->data, my_l->el_size);
	return my_l->size;
	
}

/* ************************************************** */

uint32_t list_back(list_t *const my_l, void *item){

	list_node_t *tail = list_get_sent(my_l)->prev;

	if (list_empty(my_l)){
		return 0;
	}

	memcpy(item, tail->data, my_l->el_size);
	return my_l->size;
	
}

/* ************************************************** */


/* ************************************************** */


/* ************************************************** */



