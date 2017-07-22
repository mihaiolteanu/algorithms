/* hash.h - Interface for hash table 
*/

#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include "array.h"

typedef unsigned long (*hash_fn_t)(void *elem_addr);

typedef struct {
	array *a;      	          /* Array of linked lists */
	unsigned long table_size; /* Size of the hash table */
	size_t tsize;             /* Stored element size */
	hash_fn_t hash_fn;        /* Hash function */
	comp_fn_t comp;           /* For solving collisions */
} hash_table;

extern void *hash_init(hash_table *h, size_t elem_size,
		       hash_fn_t hash_fn, comp_fn_t comp,
		       unsigned long table_size);
extern void *hash_search(hash_table *h, void *elem_addr);
extern void *hash_insert(hash_table *h, void *elem_addr);
extern void hash_destroy(hash_table *h);

#endif // HASH_H
