/* dict.h - Implementation of a generic dictionary
 */

#ifndef DICT_H
#define DICT_H

#include <stddef.h>
#include "array_sorted.h"

typedef struct {
	array_sorted *as;
} dict;

/* Initialize a new dictionary. The comparison function decides when two
elements of the same type are equal.*/
extern int dict_init(dict *d, size_t elem_size, int (*comp)(const void *, const void *));

/* Search for the item at address, based on the comparison function. */
extern void *dict_search(dict *d, void *elem_addr);

/* Given a data item address, add it to the set in the dictionary d. */
extern int dict_insert(dict *d, void *elem_addr);

/* Given a pointer to a given data item x in the dictionary d, remove it
from d. */
extern void dict_remove(dict *d, void *x);

/* Retrieve the item with the largest (or smallest) key from d.
This enables the dictionary to serve as a priority queue. */
extern void *dict_max(dict *d);
extern void *dict_min(dict *d);

/* Retrieve the item from d whose key is immediately before (or after) x in
sorted order. These enable us to interate through the elements of the
data structure. x should be the result of a search.*/
extern void *dict_predecessor(dict *d, void *x);
extern void *dict_successor(dict *d, void *x);

extern int *dict_destroy(dict *d);

#endif // DICT_H
