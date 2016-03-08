#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"
#include "system.h"

// downsize and free the array, if needed.
// to be called from delete/remove/free/etc operations
static int downsize_if_needed(array *a);
// double tha array capacity, if needed
static int resize_if_needed(array *a);

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
	memcpy((char *)a->data + a->size*a->tsize,
	       (char *)elem_addr,
	       a->tsize);
	a->size++;
	return resize_if_needed(a);
}

void *array_value(array *a, size_t index) {
	size_t size = a->size;
	size_t tsize = a->tsize;
	char *data = (char *)a->data;

	if (index >= size || index < 0)
		return NULL;

	return data + index*tsize;
}

int array_remove(array *a, size_t index) {
	size_t size = a->size;
	size_t tsize = a->tsize;
	char *data = (char *)a->data;

	if (index >= size || index < 0)
		return OK;

	char *dest = data + index*tsize;
	char *src = data + (index+1)*tsize;
	size_t elems = (size - index - 1)*tsize;
	memmove(dest, src, elems);
	a->size--;
	return downsize_if_needed(a);
}

int array_size(array *a) {
	size_t size = a->size;

	return size;
}

int array_cap(array *a) {
	size_t cap = a->cap;

	return cap;
}

extern void array_destroy(array *a) {
	free(a->data);
}

static int resize_if_needed(array *a) {
	size_t size = a->size;
	size_t cap = a->cap;
	size_t tsize = a->tsize;
	char *data = (char *)a->data;

	if (size < cap)
		return OK;
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
	char *data = (char *)a->data;

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
