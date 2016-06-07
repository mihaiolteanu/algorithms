#include <stdlib.h>
#include "dict.h"
#include "system.h"

int dict_init(dict *d, size_t elem_size, comp_fn_t comp) {
	sarray *as = malloc(sizeof(sarray));
	if (as == NULL)
		return ERROR;
	d->as = as;
	return sarray_init(as, elem_size, comp);
}

void *dict_search(dict *d, void *elem_addr) {
	sarray *as = d->as;
	
	return sarray_search(as, elem_addr);
}

int dict_insert(dict *d, void *elem_addr) {
	sarray *as = d->as;

	return sarray_add(as, elem_addr);
}

void dict_remove(dict *d, void *x) {
	sarray *as = d->as;

	sarray_remove_byaddr(as, x);
}

void *dict_max(dict *d) {
	sarray *as = d->as;
	int size = sarray_size(as);

	return sarray_value(as, size - 1);
}

void *dict_min(dict *d) {
	sarray *as = d->as;
	int size = sarray_size(as);

	if (size > 0)
		return sarray_value(as, 0);
	return NULL;
}

int *dict_destroy(dict *d) {
	sarray *as = d->as;

	sarray_destroy(as);
	free(as);
}
