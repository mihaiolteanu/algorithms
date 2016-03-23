#include <stdlib.h>
#include "array_sorted.h"
#include "array.h"
#include "system.h"

int array_sorted_init(array_sorted *as, size_t elem_size,
		      int (*comp)(const void *x, const void *y)) {
	as->comp = comp;
	return array_init(as->a, elem_size);
}

int array_sorted_add(array_sorted *as, void *elem_addr) {
	array *a = as->a;

	if (array_size(a) == 0)
		return array_add(a, elem_addr); // First element
	for (int i = 0; i < array_size(a); i++) {
		void *value = array_value(a, i);
		if (as->comp(elem_addr, value) == -1)
			return array_add_at_index(a, elem_addr, i);
	}
}

void *array_sorted_value(array_sorted *as, size_t index) {
	array *a = as->a;

	return array_value(a, index);
}

void *array_sorted_search(array_sorted *as, void *elem_addr) {
	array *a = as->a;

	char *data = bsearch(elem_addr, a->data, a->size, a->tsize, as->comp);
	return data;
}	

int array_sorted_remove(array_sorted *as, size_t index) {
	return array_remove(as->a, index);
}

int array_sorted_size(array_sorted *as) {
	array *a = as->a;
	
	return array_size(a);
}
	
