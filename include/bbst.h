/* bbst.h - Generic balanced binary search tree */
#ifndef BBST_H
#define BBST_H

#include <stddef.h>
#include "system.h"
#include "bst.h"
#include "sarray.h"

typedef struct {
	bst b;
	sarray sa;
} bbst;

/* Balanced binary tree init function, simil to binary search tree init, where
   comp - comparison function for node data.
   node_comp - comparison function for nodes, used for adding bst nodes in a
   sorted array. This should just be a wrapper around the comp function. But C
   does not permit defining function at run-time (closures), so the user of the
   balanced binary tree has to write the wrapper himself.*/
extern int bbst_init(bbst *bb, size_t elem_size, comp_fn_t comp);

/* Insert a new element of elem_size bytes from the address elem_addr into the
 * bbst.*/
extern int bbst_insert(bbst *bb, void *elem_addr);

extern void *bbst_search(bbst *bb, void *elem_addr);

extern void bbst_destroy(bbst *bb);

#endif // BBST_H
