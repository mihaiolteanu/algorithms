#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "system.h"

/* Given a node from a binary search tree, insert a new node in the correct
   location given by the comparison function */
static void bst_insert_local(bst_node *node, bst_node *newnode, comp_fn_t comp);
/* Given a node and a data address, search the tree for a node that contains
   the same data. */
static void *bst_search_local(bst_node *node, void *elem_addr, comp_fn_t comp);
static void *bst_min_local(bst_node *node);
static void *bst_max_local(bst_node *node);
	
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

void *bst_search(bst *b, void *elem_addr) {
	bst_node *root = b->head;
	comp_fn_t comp = b->comp;

	return bst_search_local(root, elem_addr, comp);
}

void *bst_min(bst *b) {
	bst_node *root = b->head;

	return bst_min_local(root);
}

void *bst_max(bst *b) {
	bst_node *root = b->head;

	return bst_max_local(root);
}


static void *bst_min_local(bst_node *node) {
	if (node == NULL)
		return NULL;
	if (node->left == NULL)
		return node->data;
	return bst_min_local(node->left);
}

static void *bst_max_local(bst_node *node) {
	if (node == NULL)
		return NULL;
	if (node->right == NULL)
		return node->data;
	return bst_max_local(node->right);
}

static void *bst_search_local(bst_node *node, void *elem_addr, comp_fn_t comp) {
	if (node == NULL)
		return NULL;
	int compres = comp(node->data, elem_addr);
	if ( compres == 0)
		return node->data; // found
	if (compres > 0)
		return bst_search_local(node->left, elem_addr, comp);
	return bst_search_local(node->right, elem_addr, comp);
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

bst_node *bst_getroot(bst *b) {
	return b->head;
}

void *bst_node_value(bst_node *node) {
	return node->data;
}

bst_node *bst_node_left(bst_node *node) {
	return node->left;
}

bst_node *bst_node_right(bst_node *node) {
	return node->right;
}
