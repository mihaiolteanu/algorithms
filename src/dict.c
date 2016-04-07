#include <stdlib.h>
#include "dict.h"
#include "system.h"

int dict_init(dict *d, size_t elem_size, comp_fn_t comp) {
	array_sorted *as = malloc(sizeof(array_sorted));
	if (as == NULL)
		return ERROR;
	d->as = as;
	return array_sorted_init(as, elem_size, comp);
}

void *dict_search(dict *d, void *elem_addr) {
	array_sorted *as = d->as;
	
	return array_sorted_search(as, elem_addr);
}

int dict_insert(dict *d, void *elem_addr) {
	array_sorted *as = d->as;

	return array_sorted_add(as, elem_addr);
}

void dict_remove(dict *d, void *x) {
	array_sorted *as = d->as;

	array_sorted_remove_byaddr(as, x);
}

void *dict_max(dict *d) {
	array_sorted *as = d->as;
	int size = array_sorted_size(as);

	return array_sorted_value(as, size - 1);
}

void *dict_min(dict *d) {
	array_sorted *as = d->as;
	int size = array_sorted_size(as);

	if (size > 0)
		return array_sorted_value(as, 0);
	return NULL;
}

int *dict_destroy(dict *d) {
	array_sorted *as = d->as;

	array_sorted_destroy(as);
	free(as);
}
