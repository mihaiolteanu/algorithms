#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "queue.h"
#include "system.h"

/* Given a node from a binary search tree, insert a new node in the correct
   location given by the comparison function */
static void bst_insert_local(bst_node *node, bst_node *newnode, comp_fn_t comp);
/* Given a node and a data address, search the tree for a node that contains
   the same data. */
static bst_node *bst_search_local(bst_node *node, void *elem_addr, comp_fn_t comp);
/* Insert all the nodes from one tree into another. */
static void bst_insert_bst(bst *from, bst *to);
	
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
	newnode->parent = NULL;
	newnode->count = 1;

	// Now find a place to link it.
	if (node == NULL) {
		b->head = newnode; // First node in the tree.
		return OK;
	}
	bst_insert_local(node, newnode, b->comp);
}

void *bst_search(bst *b, void *elem_addr) {
	bst_node *root = b->head;
	bst_node *res = NULL;
	comp_fn_t comp = b->comp;

	res = bst_search_local(root, elem_addr, comp);
	if (res != NULL)
		return res->data;
	return res;
}

int bst_search_count(bst *b, void *elem_addr) {
	bst_node *root = b->head;
	bst_node *res = NULL;
	comp_fn_t comp = b->comp;

	res = bst_search_local(root, elem_addr, comp);
	if (res != NULL)
		return res->count;
	return -1;
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

static void bst_traverse_inorder_local(bst_node *node,
				       bst_visit_fn_t visit,
				       void *obj) {
	if (node == NULL)
		return;
	bst_traverse_inorder_local(node->left, visit, obj);
	visit(node->data, obj);
	bst_traverse_inorder_local(node->right, visit, obj);
}

void bst_traverse_inorder(bst *b,
			  bst_visit_fn_t visit,
			  void *obj) {
	bst_node *node = b->head;

	bst_traverse_inorder_local(node, visit, obj);
}

static void bst_traverse_preorder_local(bst_node *node,
					bst_visit_fn_t visit,
					void *obj) {
	if (node == NULL)
		return;

	visit(node->data, obj);
	bst_traverse_preorder_local(node->left, visit, obj);
	bst_traverse_preorder_local(node->right, visit, obj);
}

void bst_traverse_preorder(bst *b,
			   bst_visit_fn_t visit,
			   void *obj) {
	bst_node *node = b->head;

	bst_traverse_preorder_local(node, visit, obj);
}

static void traverse_breadth_first(queue *q,
				   bst_visit_fn_t visit,
				   void *obj) {
	/* Extract the next node from the queue. */
	bst_node *qnode = queue_dequeue(q);
	if (qnode == NULL)
		return; /* Empty queue. */
	visit(qnode->data, obj);
	/* Enqueue both node's children. */
	if (qnode->left != NULL)
		queue_enqueue(q, qnode->left);
	if (qnode->right != NULL)
		queue_enqueue(q, qnode->right);
	/* Process the rest of the queue. */
	traverse_breadth_first(q, visit, obj);
}

void bst_traverse_breadth_first(bst *b, bst_visit_fn_t visit, void *obj) {
	queue q;
	size_t btsize = b->tsize;
	bst_node *head = b->head;

	/* Hold the nodes to be visited in a queue. */
	queue_init(&q, sizeof(bst_node) + btsize);
	queue_enqueue(&q, head);
	traverse_breadth_first(&q, visit, obj);
}

static bst_node *bst_search_local(bst_node *node, void *elem_addr, comp_fn_t comp) {
	if (node == NULL)
		return NULL;
	int compres = comp(node->data, elem_addr);
	if ( compres == 0)
		return node; // found
	if (compres > 0)
		return bst_search_local(node->left, elem_addr, comp);
	return bst_search_local(node->right, elem_addr, comp);
}

static void bst_insert_local(bst_node *node, bst_node *newnode, comp_fn_t comp) {
	bst_node *left = node->left;
	bst_node *right = node->right;
	
	int compres = comp(newnode->data, node->data);
	if (compres < 0)
		if (left == NULL) {
			node->left = newnode;
			newnode->parent = node;
		}
		else
			bst_insert_local(left, newnode, comp);
	else if (compres > 0)
		if (right == NULL) {
			node->right = newnode;
			newnode->parent = node;
		}
		else
			bst_insert_local(right, newnode, comp);
	else
		node->count++;
}

/* Visiting function that inserts the element into the bst. */
static int h_bst_visit_insert(void *elem_addr, bst *b) {
	/* Already have an insert function but with switched params. */
	return bst_insert(b, elem_addr);
}

static void bst_insert_bst(bst *from, bst *to) {
	/* Traverse the tree, adding each found node in the destination tree.*/
	bst_traverse_breadth_first(from, h_bst_visit_insert, to);
}

static bst_node *fill_find_node(bst_node *node,
			int (*check_fill)(void *node_data, void *elem_addr),
			void *elem_addr) {
	bst_node *tmp_node = NULL;

	if (node == NULL)
		return NULL;

	int check_fill_res = check_fill(node->data, elem_addr);

	if (check_fill_res == 0)
		/* Node can be filled completely. Perfect match! */
		return node;

	if (check_fill_res > 0) // Overfill.
		return fill_find_node(node->left, check_fill, elem_addr);

	if (check_fill_res < 0) { // Underfill.
		tmp_node = fill_find_node(node->right, check_fill, elem_addr);
		if (tmp_node == NULL)
			/* All the other nodes are either NULL or would overfill
			 * so keep this one.*/
			return node;
		return tmp_node;
	}
}

void bst_fill(bst *b,
	      int (*check_fill)(void *node_data, void *elem_addr),
	      void (*fill)(void *node_data, void *elem_addr),
	      void *elem_addr) {
	bst_node *node = b->head;
	bst_node *node_tofill = NULL;
	bst_node *parent = NULL;

	node_tofill = fill_find_node(node, check_fill, elem_addr);

	if (node_tofill == NULL)
		/* No suitable position found, so add a new node with the given
		 * data. */
		bst_insert(b, elem_addr);
	else {
		/* Update the node with the given data. */
		fill(node_tofill->data, elem_addr);
		parent = node_tofill->parent;
		/* Find if the filled node was left or right sibbling and
		 * detach the filled node from the tree. */
		if (parent->left == node_tofill)
			parent->left = NULL;
		else
			parent->right = NULL;

		/* Reinsert the detached node and all of its children to the
		 * initial tree. */
		bst temp_bst;
		bst_init(&temp_bst, b->tsize, b->comp);
		temp_bst.head = node_tofill;
		bst_insert_bst(&temp_bst, b);
	}
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
