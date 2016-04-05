/* array_sorted.h - Implementation of a resizable sorted array
 */

#ifndef ARRAY_SORTED_H
#define ARRAY_SORTED_H

#include <stddef.h>
#include "array.h"

typedef struct {
	int (*comp)(const void *, const void *); // Comparison function
	array *a;
} array_sorted;

/* Initialize a new generic resizable sorted array, where each element in the
array has elem_size. The comparison function is used to decide the order
of the new added elements in the array. */
extern int array_sorted_init(array_sorted *as, size_t elem_size,
			     int (*comp)(const void *x, const void *y));

/* Add the element at elem_addr to the sorted array, using the compare
function specified in the initialization. */
extern int array_sorted_add(array_sorted *as, void *elem_addr);

extern void *array_sorted_value(array_sorted *as, size_t index);
extern void *array_sorted_search(array_sorted *as, void *elem_addr);
extern int array_sorted_remove_byindex(array_sorted *as, size_t index);
extern int array_sorted_remove_byaddr(array_sorted *as, void *elem_addr);
extern int array_sorted_size(array_sorted *as);
extern int array_sorted_cap(array_sorted *as);
extern void array_sorted_destroy(array_sorted *as);

#endif // ARRAY_SORTED_H
