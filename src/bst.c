#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "system.h"

/* Given a node from a binary search tree, insert a new node in the correct
   location given by the comparison function */
static void bst_insert_local(bst_node *node, bst_node *newnode, comp_fn_t comp);

int bst_init(bst *b, size_t elem_size, comp_fn_t comp) {
	b->tsize = elem_size;
	b->comp = comp;
	b->head = NULL; // Initialize an empty tree.

	return OK;
}

int bst_insert(bst *b, void *elem_addr) {
	size_t tsize = b->tsize;
	bst_node *node = b->head;

	// Initialize a new node with the given data.
	bst_node *newnode = malloc(sizeof(bst_node) +
				  tsize); // For node data (zero-length array)
	if (newnode == NULL)
		return ERROR;
	memcpy(newnode->data, elem_addr, tsize);
	newnode->left = NULL;
	newnode->right = NULL;

	// Now find a place to link it.
	if (node == NULL) {
		b->head = newnode; // First node in the tree.
		return OK;
	}
	bst_insert_local(node, newnode, b->comp);
}

static void bst_insert_local(bst_node *node, bst_node *newnode, comp_fn_t comp) {
	bst_node *left = node->left;
	bst_node *right = node->right;
	
	int compres = comp(newnode->data, node->data);
	if (compres < 0)
		if (left == NULL)
			node->left = newnode;
		else
			bst_insert_local(left, newnode, comp);
	else
		if (right == NULL)
			node->right = newnode;
		else
			bst_insert_local(right, newnode, comp);
}