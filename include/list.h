/* linkedlist.h
   Implementation of a generic linked list
*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list_node_t {
	struct list_node_t *next;
	char data[0]; // GCC zero-length array
	              // should be made equal to list.tsize
} list_node;

typedef struct {
	size_t tsize;
	list_node *head;
} list;


extern void list_init(list *l, size_t elem_size);

extern int list_add(list *l, void *elem_addr);

// l          - list pointer
// src_addr   - address of element to be searched (possible the address of
//              a struct variable
// struct_pos - address relative to the src_addr from which to compare
//              if zero, compare the whole address. For a struct, compare
//              only that element of the struct, and this value should be
//              the address of the element minus the address of the struct
//              variable.
// elem_size  - this is the size of the element to be compared. For a
//              struct, it is the size of the element to be compared.
extern void *list_search(list *l, void *src_addr, size_t struct_pos, size_t elem_size);





#endif // LIST_H
