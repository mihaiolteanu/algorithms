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
	bst_node *node = b->head;

	if (node == NULL)
		return NULL;
	while (node->left != NULL)
		node = node->left;
	return node->data;
}

void *bst_max(bst *b) {
	bst_node *node = b->head;

	if (node == NULL)
		return NULL;
	while(node->right != NULL)
		node = node->right;
	return node->data;
}

static void bst_traverse_inorder_local(bst_node *node, void (*visit)(void *)) {
	if (node == NULL)
		return;
	bst_traverse_inorder_local(node->left, visit);
	visit(node->data);
	bst_traverse_inorder_local(node->right, visit);
}

void bst_traverse_inorder(bst *b, void (*visit)(void *)) {
	bst_node *node = b->head;

	bst_traverse_inorder_local(node, visit);
}

static void bst_traverse_preorder_local(bst_node *node, void (*visit)(void *)) {
	if (node == NULL)
		return NULL;

	visit(node->data);
	bst_traverse_preorder_local(node->left, visit);
	bst_traverse_preorder_local(node->right, visit);
}

void bst_traverse_preorder(bst *b, void (*visit)(void *)) {
	bst_node *node = b->head;

	bst_traverse_preorder_local(node, visit);
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
