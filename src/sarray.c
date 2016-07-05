#include <stdlib.h>
#include "sarray.h"
#include "array.h"
#include "system.h"

int sarray_init(sarray *as, size_t elem_size, comp_fn_t comp) {
	array *a = malloc(sizeof(array));
	if (a == NULL)
		return ERROR;
	as->a = a;
	as->comp = comp;
	return array_init(as->a, elem_size, NULL);
}

int sarray_add(sarray *as, void *elem_addr) {
	array *a = as->a;

	// First element
	if (array_size(a) == 0)
		return array_add(a, elem_addr);

	// Find the position before the first element greater or equal
	// than this new element and insert the new element there.
	for (int i = 0; i < array_size(a); i++) {
		void *value = array_value(a, i);
		int comp_res = as->comp(elem_addr, value);
		if (comp_res <= 0)
			return array_add_at_index(a, elem_addr, i);
	}
	// This is the greatest element so far, so insert at the end.
	return array_add(a, elem_addr);
}

void *sarray_value(sarray *as, size_t index) {
	array *a = as->a;

	return array_value(a, index);
}

void *sarray_search(sarray *as, void *elem_addr) {
	array *a = as->a;

	char *data = bsearch(elem_addr, a->data, a->size, a->tsize, as->comp);
	return data;
}	

int sarray_remove_byindex(sarray *as, size_t index) {
	return array_remove_byindex(as->a, index);
}

int sarray_remove_byaddr(sarray *as, void *elem_addr) {
	return array_remove_byaddr(as->a, elem_addr);
}

int sarray_size(sarray *as) {
	array *a = as->a;
	
	return array_size(a);
}
	
void sarray_destroy(sarray *as) {
	array *a = as->a;

	array_destroy(a);
	free(a);
}
