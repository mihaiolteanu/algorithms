/* linkedlist.h
   Implementation of a generic linked list. Define your own functions
   for specific data types, for ease of use.

*** Example for a linked list of a city structure containing size and
*** population elements

typedef struct city_t {
	size_t size;
	size_t pop;
} city;

static void list_city_init(list *l) {
	list_init(l, sizeof(city));
}

static int list_city_add(list *l, city *c) {
	return list_add(l, c);
}

static city *list_city_search_size(list *l, size_t size) {
	return (city *)list_search(l,
				   &size, 
				   0, // (char *) city.size - (char *) city.size
				   sizeof(size_t) // sizeof(city.size)
		);
}

static city *list_city_search_pop(list *l, size_t pop) {
	return (city *)list_search(l,
				   &pop,
				   4, // (char *)city.pop - (char *)city.size 
				   sizeof(size_t) // sizeof(city.pop)
		);
}

int main(void) {
	list l;
	city re = { 24, 34 };
	city si = { 55, 150 };

	list_city_init(&l);
	list_city_add(&l, &re);
	list_city_add(&l, &si);

	city *result = list_city_search_pop(&l, 150);
	if (result == NULL)
		printf("not found\n");
	else
		printf("size: %d, pop: %d", result->size, result->pop);
	printf("\n");

	return 0;
}
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
// pos        - address relative to the src_addr from which to compare
//              if zero, compare the whole address. For a struct, compare
//              only that element of the struct, and this value should be
//              the address of the element minus the address of the struct
//              variable.
// elem_size  - this is the size of the element to be compared. For a
//              struct, it is the size of the element to be compared.
// Returns the address of the searched item, NULL if not found.
// *return_addr == *(src_addr + pos)
extern void *list_search(list *l, void *src_addr, size_t pos, size_t elem_size);

extern void list_remove(list *l, void *src_addr, size_t pos, size_t elem_size);

extern void list_reverse(list *l);

#endif // LIST_H
