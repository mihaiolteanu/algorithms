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
	comp_fn_t node_comp;
} bbst;

extern int bbst_init(bbst *bb, size_t elem_size,
		     comp_fn_t comp,
		     comp_fn_t node_comp);
extern int bbst_insert(bbst *bb, void *elem_addr);

#endif // BBST_H
