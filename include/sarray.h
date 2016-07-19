/* sarray.h - Implementation of a resizable sorted array
 */

#ifndef ARRAY_SORTED_H
#define ARRAY_SORTED_H

#include <stddef.h>
#include "system.h"
#include "array.h"

typedef struct {
	comp_fn_t comp;
	array *a;
} sarray;

/* Initialize a new generic resizable sorted array, where each element in the
array has elem_size. The comparison function is used to decide the order
of the new added elements in the array. */
extern int sarray_init(sarray *as, size_t elem_size, comp_fn_t comp);

/* Add the element at elem_addr to the sorted array, using the compare
function specified in the initialization. */
extern int sarray_add(sarray *as, void *elem_addr);

extern void *sarray_value(sarray *as, size_t index);
extern void *sarray_search(sarray *as, void *elem_addr);
extern int sarray_remove_byindex(sarray *as, size_t index);
extern int sarray_size(sarray *as);
extern int sarray_cap(sarray *as);
extern void sarray_destroy(sarray *as);

#endif // ARRAY_SORTED_H
