/* linkedlist.h
   Implementation of a generic linked list. Define your own functions
   for specific data types, for ease of use. */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "system.h"

typedef struct list_node_t {
	struct list_node_t *next;
	char data[0]; // GCC zero-length array
	              // should be made equal to list.tsize
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

// Reverse the linked list.
extern void list_reverse(list *l);

// Recursively reverse the linked list. Because it's fun.
extern void list_reverse_rec(list *l);

#endif // LIST_H
