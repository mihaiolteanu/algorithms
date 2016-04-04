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

int array_init(array *a, size_t elem_size) {
	a->size = 0;
	a->cap = INIT_CAP;
	a->tsize = elem_size;
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

extern int array_add_at_index(array *a, void *elem_addr, size_t index) {
	char *data = a->data;
	size_t size = a->size;
	size_t tsize = a->tsize;

	increment_size(a);
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

void *array_search(array *a, void *elem_addr,
		   int (*comp)(void *x, void *y)) {
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

int array_remove_byaddr(array *a, void *addr) {
	// The easiest way is to calculate the index, based on the base
	// address of the array and the address of the element to removed
	// and the element size
	size_t tsize = a->tsize;
	char *data = a->data;
	ptrdiff_t diffbytes = (char *)addr - data;
	size_t index = diffbytes / tsize;

	return array_remove_byindex(a, index);
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
