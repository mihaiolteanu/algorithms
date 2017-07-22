/* linkedlist.h
   Implementation of a generic linked list. Define your own functions
   for specific data types, for ease of use. */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "system.h"

typedef struct list_node_t {
	struct list_node_t *next;
	char *data;
} list_node;

typedef struct {
	size_t tsize;
	comp_fn_t comp;
	list_node *head;
} list;

/* Initialize a linked list object. The data items will have elem_size
   number of bytes. The comparison function is used for searching. */
extern void list_init(list *l, size_t elem_size, comp_fn_t comp);

/* Add a new node to the linked list. The contents at the given address
   are copied to the data field of the new node. */
extern int list_add(list *l, void *elem_addr);

/* Search for a node in the list using the comparison function given in the
   init function. Returns the address of the item, if found, NULL otherwise.*/
extern void *list_search(list *l, void *src_addr);

/* Remove a node from the list. Use the comparison function given in the init
   to decide which element is equal to the element at src_addr. */
extern void list_remove(list *l, void *src_addr);

/* Return a pointer to the first node in the linked list. Return NULL if there
 * a re no nodes in the list. */
extern list_node *list_first_node(list *l);

/* Return a pointer to the next node in the linked list. Return NULL if this is
 * the last node in the list. */
extern list_node *list_next_node(list_node *node);

/* Return the data stored in the list node. */
extern void *list_node_data(list_node *node);

// Reverse the linked list.
extern void list_reverse(list *l);

/* Destroy the array */
extern void list_destroy(list *);

// Recursively reverse the linked list. Because it's fun.
extern void list_reverse_rec(list *l);

#endif // LIST_H
