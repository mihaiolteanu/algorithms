/* bst.h - Generic binary search tree */
#ifndef BST_H
#define BST_H

#include <stddef.h>
#include "system.h"

typedef struct bst_node_t {
	struct bst_node_t *left;
	struct bst_node_t *right;
	struct bst_node_t *parent;
	int count;    /* Number of nodes with the same key. */
	char *data;
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
   copied are equal to the elem_size given in the init function. Returns the
   newly created node containing the data from elem_addr. */
extern bst_node *bst_insert(bst *b, void *elem_addr);

/* Insert an already existing node into the bst using the node comparison
 * function to decide the node location. */
extern bst_node *bst_insert_node(bst *b, bst_node *node);

/* Search for the item at elem_address in the tree. The comparison function
given in the init function is used to decide when two items from the tree
are equal. Returns the node address from the tree if found, NULL othrwise.*/
extern void *bst_search(bst *b, void *elem_addr);

/* Search using a different comparison function than the one from the init
   and return the bst_node, NOT the node data.
   Hackish. First used in e_03_13 to traverse the tree from a leaf node up to
   the root of the tree.*/
extern void *bst_search_with_comp(bst *b, void *elem_addr, comp_fn_t comp);

/* Search for the item at elem_address in the tree. Return the number of nodes
   that have the same key as the searched item, -1 if not found. */
extern int bst_search_count(bst *b, void *elem_addr);

/* Find the min/max node data from the tree. */
extern void *bst_min(bst *b);
extern void *bst_max(bst *b);

/* Returns number of nodes in the bst. */
extern int bst_count(bst *b);

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

/* Traverse the tree in a breadth first fashion calling the visit function on
 * each visited node. */
extern void bst_traverse_breadth_first(bst *b, bst_visit_fn_t visit, void *obj);

/* Checks if the current node data from the tree can be filled with the data at 
   elem_addr. Returns 0 if fill is 100%, -1 if underfill and 1 if overfill. */
typedef int (*bst_check_fill_fn_t)(void *node_data, void *elem_addr);

/* Fills the node data with the contents at elem_addr. */
typedef int (*bst_fill_fn_t)(void *node_data, void *elem_addr);

/* Modify an existing node according to the fill function. Only create a new
   node if no other node can be modified to the fill function's liking. The
   affected node and all its children are reinserted in the tree to mantain
   the bst invariant. First used for the best-fit heuristic for the bin packing
   problem (3-10) */
extern void bst_fill(bst *b,
		     bst_check_fill_fn_t check_fill,
		     bst_fill_fn_t fill,
		     void *elem_addr);

// ***** Functions mostly used for tests *****
/* Get the root of the tree. */
extern bst_node *bst_getroot(bst *b);

/* Get the value of the given node. */
extern void *bst_node_value(bst_node *node);

/* Get the left node of the given node. */
extern bst_node *bst_node_left(bst_node *node);

/* Get the right node of the given node. */
extern bst_node *bst_node_right(bst_node *node);

/* Get the parent of the given node. */
extern bst_node *bst_node_parent(bst_node *node);

#endif // BST_H
