/* 3-4. [3] Design a dictionary data structure in which search, insertion, and
deletion can all be processed in O(1) time in the worst case. You may assume
the set elements are integers drawn from a finite set 1, 2, .., n, and
initialization can take O(n) time. */

#include <stdlib.h>
#include "e03_04.h"

static int e03_04dict_setreset_value(e03_04dict *d, int value, int setreset) {
	int *a = d->a;
	int size = d->size;

	if (value > size)
		return -1;
	a[value - 1] = setreset;
}

int e03_04dict_init(e03_04dict *d, int size) {
	d->a = calloc(size, sizeof(int));
	if (d->a == NULL)
		return -1;
	d->size = size;
	return 0;
}

// Returns FREE if not found, USED if found, -1 if no such index.
int e03_04dict_search(e03_04dict *d, int value) {
	int *a = d->a;
	int size = d->size;

	if (value > size)
		return -1;
	return a[value];
}

int e03_04dict_insert(e03_04dict *d, int value) {
	e03_04dict_setreset_value(d, value, E03_04SET);
}
	
int e03_04dict_delete(e03_04dict *d, int value) {
	e03_04dict_setreset_value(d, value, E03_04RESET);
}

