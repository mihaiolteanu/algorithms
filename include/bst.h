/* bst.h - Generic binary search tree */
#ifndef BST_H
#define BST_H

#include <stddef.h>
#include "system.h"

typedef struct bst_node_t {
	struct bst_node_t *left;
	struct bst_node_t *right;
	char data[0]; // GCC zero-length array
} bst_node;

typedef struct {
	size_t tsize; // Size of each node data.
	comp_fn_t comp;
	bst_node *head;
} bst;

/* Initialize a binary tree with the given node data size. The comparison
   function is used to search the tree */
extern int bst_init(bst *b, size_t elem_size, comp_fn_t comp);

/* Insert the contents at elem_addr in the binary tree. The number of bytes
   copied are equal to the elem_size given in the init function. */
extern int bst_insert(bst *b, void *elem_addr);

/* Search for the item at elem_address in the tree. The comparison function
given in the init function is used to decide when two items from the tree
are equal. Returns the node address from the tree if found, NULL othrwise.*/
extern void *bst_search(bst *b, void *elem_addr);

#endif // BST_H
