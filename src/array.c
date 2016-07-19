#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"
#include "system.h"

// downsize and free the array, if needed.
// to be called from delete/remove/free/etc operations
static int downsize_if_needed(array *a);
// increment the array size and double tha array capacity, if needed
static int increment_size(array *a);

int array_init(array *a, size_t elem_size, comp_fn_t comp) {
	a->size = 0;
	a->cap = INIT_CAP;
	a->tsize = elem_size;
	a->comp = comp;
	a->data = malloc(INIT_CAP*elem_size);
	if (a->data == NULL)
		return ERROR;
	return OK;
}

int array_add(array *a, void *elem_addr) {
	memcpy(a->data + a->size*a->tsize,
	       elem_addr,
	       a->tsize);
	return increment_size(a);
}

int array_add_at_index(array *a, void *elem_addr, size_t index) {
	char *data;
	size_t size = a->size;
	size_t tsize = a->tsize;

	/* What should the missing indexes be filled with?! */
	if (index > size)
		return -1;

	increment_size(a);
	data = a->data;
	size = a->size;
	// Shift one position to the right, starting from the index, to make
	// room for the new element.
	memmove(data + (index+1)*tsize,
		data + index*tsize,
		(size - index)*tsize);
	// Copy the new element from the end to the new available location.
	memcpy(data + index*tsize,
	       elem_addr,
	       tsize);
}

void *array_value(array *a, size_t index) {
	size_t size = a->size;
	size_t tsize = a->tsize;
	char *data = a->data;

	if (index >= size || index < 0)
		return NULL;

	return data + index*tsize;
}

void *array_search(array *a, void *elem_addr) {
	comp_fn_t comp = a->comp;
	if (comp == NULL)
		return NULL;
	for (int i = 0; i < array_size(a); i++) {
		void *elem = array_value(a, i);
		if (comp(elem_addr, elem) == 0)
			return elem; // found
	}
	return NULL;
}

int array_remove_byindex(array *a, size_t index) {
	size_t size = a->size;
	size_t tsize = a->tsize;
	char *data = a->data;

	if (index >= size || index < 0)
		return OK;

	char *dest = data + index*tsize;
	char *src = data + (index+1)*tsize;
	size_t elems = (size - index - 1)*tsize;
	memmove(dest, src, elems);
	a->size--;
	return downsize_if_needed(a);
}

void array_qsort(array *a, int (*compar)(const void *x, const void *y)) {
	qsort(a->data, a->tsize, a->size, compar);
}

int array_size(array *a) {
	size_t size = a->size;

	return size;
}

int array_cap(array *a) {
	size_t cap = a->cap;

	return cap;
}

void array_destroy(array *a) {
	free(a->data);
}

static int increment_size(array *a) {
	size_t size = ++a->size;
	size_t cap = a->cap;
	size_t tsize = a->tsize;
	char *data = a->data;

	if (size < cap)
		return OK; // nothing to do
	void *tmp_data = realloc(data, 2*cap*tsize);
	if (tmp_data == NULL)
		return ERROR;
	a->cap = 2*cap;
	a->data = tmp_data;
	return OK;
}		

/* 3-3.
   helper function for implementing a solution to exercise 3-3 (a) */
static int downsize_if_needed(array *a) {
	size_t size = a->size;
	size_t cap = a->cap;
	size_t tsize = a->tsize;
	char *data = a->data;

	// Downsize if number of elements are half the capacity
	// and the capacity is not lower than the initial capacity
	if (size >= cap/2 || cap <=INIT_CAP )
		return OK;
	void *tmp_data = realloc(data, cap*tsize/2);
	if (tmp_data == NULL)
		return ERROR;
	a->cap = cap/2;
	a->data = tmp_data;
	return OK;
}
