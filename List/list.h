
/**
 * @file list.h
 * @author Juan Manuel Torres Palma
 * @brief Generic C list declaration file
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h> // For size_t

/*
 * @brief A generic double linked list struct using nodes as containers.
 * Internally uses a double linked list scheme.
 * @var head Pointer to the head node of the list.
 * @var el_size Size of each element in the list. Should be constant.
 * @var size Current size of the list.
 */
typedef struct list{
	void *head;			/* Pointer to first node */	
	void *tail;			/* Pointer to last node */	
	size_t el_size;		/* Element size. Should be constant */
	unsigned int size;	/* Number of elements in the list */	
} list_t; 

/*
 * @brief Iterator to go over the list and find positions.
 * Solution for delete, insert and search functions. 
 */
typedef void * list_iterator_t;

/*
 * @brief Initialize a new list.
 * @param [in] my_l Pointer to the list to be initialized.
 * @param [in] size Size in bytes of a single element.
 * @code
 * 		list_init(&l, sizeof(int));
 * @endcode 
 */
void list_init(list_t *const my_l, size_t size);
 
/*
 * @brief Destroy the list and free its resources.
 * @param my_list Pointer to the list to be freed up.
 */
void list_destroy(list_t *const my_list);

/*
 * @brief Adds a new element to the end of list.
 * @param [in] my_list Pointer to the list where will add the item.
 * @param [in] item Pointer to the item to be attached.
 */
void list_push_back(list_t *const my_list, void *item);

/*
 * @brief Removes an element from the end of list.
 * @param [in] my_list Pointer to the list to get an item removed.
 * @param [out] item Pointer to a variable to store the removed value.
 * Could be NULL.
 * @return Number of elements remaining in the list.
 */
unsigned int list_pop_back(list_t *const my_list, void *item);

/*
 * @brief Attaches a new element to the head of the list.
 * @param [in] my_list Pointer to the list to be modified.
 * @param [in] item Pointer to the item to be stored.
 */
void list_push_front(list_t *const my_list, void *item);

/*
 * @brief Returns the top element of the list and deletes it.
 * @param [in] my_list Pointer to the list to be popped.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_list.
 */
unsigned int list_pop_front(list_t *const my_list, void *item);

/*
 * @brief Gets the first element in the list.
 * @param [in] my_list Pointer to the list to be checked.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_list.
 */
unsigned int list_front(list_t *const my_list, void *item);

/*
 * @brief Gets the last element in the list.
 * @param [in] my_list Pointer to the list to be checked.
 * @param [out] item Pointer to the item where will store the value.
 * @return Number of elements remaining in my_list.
 */
unsigned int list_back(list_t *const my_list, void *item);

/*
 * @brief Checks if the list is empty.
 * @param [in] my_list Pointer to the list to be checked.
 * @return Status of the list.
 * @retval 1 Empty list.
 * @retval 0 Not empty list.
 */
static inline unsigned char list_empty(list_t *const my_l)
{
	return (my_l->size == 0);
}

/*
 * @brief Returns the number of allocated items.
 * @param [in] my_list Pointer to the list to be checked.
 * @return Number of items in the list.
 */
static inline unsigned int list_size(list_t *const my_list)
{
	return my_list->size;
}

/*
 * @brief Finds an item in the list, and returns a pointer to the value.
 * @param [in] my_list Pointer to the list to search in.
 * @param [in] s_itm Pointer to the searched item.
 * @param [out] f_itm Pointer to iterator. Will receive the searched value.
 * @return Integer showing success or not.
 * @retval 1 Found item.
 * @retval 0 Not found item.
 */
unsigned char list_search(list_t *const my_list, void *const s_itm, 
							list_iterator_t *const f_itm);

/*
 * @brief Insert an item in the list, in the position given.
 * @param [in] my_list Pointer to the list to insert in.
 * @param [in] indx Iterator pointing to where the item will be stored.
 * @param [out] f_itm Pointer to the item to insert.
 * @return Integer showing success or not.
 * @retval 1 Found item.
 * @retval 0 Not found item.
 */
unsigned char list_insert(list_t *const my_list, const list_iterator_t indx,
							void *const item);

/*
 * @brief Removes an item from the list. The first coincidence.
 * @param [in] my_list Pointer to the list to delete from.
 * @param [in] indx Iterator where we want to insert.
 */
void list_delete(list_t *const my_list, const list_iterator_t indx);

#endif /* LIST_H_ */
