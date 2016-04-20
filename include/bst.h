/* bst.h - Generic binary search tree */
#ifndef BST_H
#define BST_H

#include <stddef.h>
#include "system.h"

typedef struct bst_node_t {
	struct bst_node_t *left;
	struct bst_node_t *right;
	int count;    /* Number of nodes with the same key. */
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

/* Search for the item at elem_address in the tree. Return the number of nodes
   that have the same key as the searched item. */
extern int bst_search_count(bst *b, void *elem_addr);

/* Find the min/max node data from the tree. */
extern void *bst_min(bst *b);
extern void *bst_max(bst *b);

/* Function type for visit function to be caled for each node. Used for tree
   traversal. */
typedef void (*bst_visit_fn_t)(void *visited, void *obj);

/* Do an in-order traversal of the binary tree and call the visit function
   for each visited node. The visit function is called with the node data
   and object as arguments. */
extern void bst_traverse_inorder(bst *b, bst_visit_fn_t visit, void *obj);

/* Do a pre-order traversal of the binary tree and call the visit function
   for each visited node. The visit function is called with the node data
   and object as arguments. */
extern void bst_traverse_preorder(bst *b, bst_visit_fn_t visit, void *obj);

// ***** Functions mostly used for tests *****
/* Get the root of the tree. */
extern bst_node *bst_getroot(bst *b);

/* Get the value of the given node. */
extern void *bst_node_value(bst_node *node);

/* Get the left node of the given node. */
extern bst_node *bst_node_left(bst_node *node);

/* Get the right node of the given node. */
extern bst_node *bst_node_right(bst_node *node);

#endif // BST_H
