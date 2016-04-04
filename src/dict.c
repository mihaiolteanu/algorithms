#include <stdlib.h>
#include "dict.h"
#include "system.h"

int dict_init(dict *d, size_t elem_size,
	      int (*comp)(const void *, const void *)) {
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

int *dict_destroy(dict *d) {
	array_sorted *as = d->as;

	array_sorted_destroy(as);
	free(as);
}
