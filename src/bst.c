#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "queue.h"
#include "system.h"

/* Given a node from a binary search tree, insert a new node in the correct
   location given by the comparison function */
static void insert(bst_node *node, bst_node *newnode, comp_fn_t comp);
/* Given a node and a data address, search the tree for a node that contains
   the same data. */
static bst_node *search(bst_node *node, void *elem_addr, comp_fn_t comp);
/* Search for a node in the bst. If comp_param is not null, use it instead of
 * the default comparison function. */
static bst_node *search_node(bst *b, void *elem_addr, comp_fn_t comp_param);
/* Visiting function that inserts the element into the bst. */
static void visit_insert(void *elem_addr, bst *b);
/* Insert all the nodes from one tree into another. */
static void insert_bst(bst *from, bst *to);
/* Create a new node containing tsize bytes from the elem_addr. */
static bst_node *new_node(size_t tsize, void *elem_addr);
/* Traverse the tree, visiting the node structure. */
static void traverse_inorder_visit_node(bst_node *node,
					bst_visit_fn_t visit,
					void *obj);
/* Traverse the tree, visiting the node data. */
static void traverse_inorder_visit_node_data(bst_node *node,
					     bst_visit_fn_t visit,
					     void *obj);
/* Each node visit increases the result count. */
static void visit_count(bst_node *node, int *res);
/* Recursively traverse the bst in a preorder manner. */
static void traverse_preorder(bst_node *node,
			      bst_visit_fn_t visit,
			      void *obj);
/* Recursively traverse the bst in a breadth first manner. */
static void traverse_breadth_first(queue *q,
				   bst_visit_fn_t visit,
				   void *obj);
/* Recursivelly find node to fill. */
static bst_node *fill_find_node(bst_node *node,
				bst_check_fill_fn_t check_fill,
				void *elem_addr);


int bst_init(bst *b, size_t elem_size, comp_fn_t comp) {
	b->tsize = elem_size;
	b->comp = comp;
	b->head = NULL; // Initialize an empty tree.

	return OK;
}

bst_node *bst_insert(bst *b, void *elem_addr) {
	size_t tsize = b->tsize;
	bst_node *head = b->head;
	bst_node *newnode = new_node(tsize, elem_addr);

	if (newnode == NULL)
		return NULL;
	if (head == NULL) {
		b->head = newnode; /* Newnode becomes the head. */
		return newnode;
	}
	insert(head, newnode, b->comp);
	return newnode;
}

bst_node *bst_insert_node(bst *b, bst_node *newnode) {
	bst_node *head = b->head;

	if (newnode == NULL)
		return NULL; /* Nothing to do. */
	if (head == NULL) {
		b->head = newnode; /* First node. */
		return newnode;
	}
	insert(head, newnode, b->comp);
	return newnode;
}

void *bst_search(bst *b, void *elem_addr) {
	bst_node *res = search_node(b, elem_addr, NULL);
	if (res != NULL)
		return res->data;
	return res;
}

void *bst_search_with_comp(bst *b, void *elem_addr, comp_fn_t comp) {
	return search_node(b, elem_addr, comp);
}

int bst_search_count(bst *b, void *elem_addr) {
	bst_node *res = search_node(b, elem_addr, NULL);
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

int bst_count(bst *b) {
	int res = 0;
	traverse_inorder_visit_node(b->head, (bst_visit_fn_t)visit_count, &res);
	return res;
}

static void nodes_collect(bst_node *node, array *nodes) {
        /* Add the pointer to node, so that I can free it later. */
	array_add(nodes, &node);
}

/* Collect all the nodes in an array and deallocate them. Otherwise, I can't get
 * to the node children if I deallocate it as I visit the node. */
void bst_destroy(bst *b) {
	array a;
	bst_node *node;

	array_init(&a, sizeof(bst_node*), NULL);
	traverse_inorder_visit_node(b->head, (bst_visit_fn_t)nodes_collect, &a);
	for (int i = 0; i < array_size(&a); i++) {
		node = *(bst_node**)array_value(&a, i);
		free(node->data);
		free(node);
	}
	b->head = NULL;
        array_destroy(&a);
}

void bst_traverse_inorder(bst *b,
			  bst_visit_fn_t visit,
			  void *obj) {
	bst_node *node = b->head;

	traverse_inorder_visit_node_data(node, visit, obj);
}

void bst_traverse_preorder(bst *b,
			   bst_visit_fn_t visit,
			   void *obj) {
	bst_node *node = b->head;

	traverse_preorder(node, visit, obj);
}

void bst_traverse_breadth_first(bst *b, bst_visit_fn_t visit, void *obj) {
	queue q;
	size_t btsize = b->tsize;
	bst_node *head = b->head;

	/* Hold the nodes to be visited in a queue. */
	queue_init(&q, sizeof(bst_node));
	queue_enqueue(&q, head);
	traverse_breadth_first(&q, visit, obj);
}

void bst_fill(bst *b,
	      bst_check_fill_fn_t check_fill,
	      bst_fill_fn_t fill,
	      void *elem_addr) {
	bst_node *candidate, *parent; /* Node to be filled and it's parent. */

	if ((candidate = fill_find_node(b->head, check_fill,elem_addr)) == NULL)
		/* All buckets would overfill, create a new bucket. */
		bst_insert(b, elem_addr);
	else {
		/* There might be multiple nodes with the same key. */
		if (candidate->count > 1) {
			/* Take out an instance of a node. */
			candidate->count--;
			candidate = new_node(b->tsize, candidate->data);
			fill(candidate->data, elem_addr);
			bst_insert(b, candidate->data);
			return;
		}
		fill(candidate->data, elem_addr);
		if ((parent = candidate->parent) != NULL) { /* Not the root. */
			/* Find if the filled node was left or right sibbling
			 * and detach the filled node from the tree. */
			if (parent->left == candidate)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else
			b->head = NULL; /* Detach the whole tree. */
		/* Reinsert the detached node and all of its children to the
		 * initial tree. */
		bst temp_bst;
		bst_init(&temp_bst, b->tsize, b->comp);
		temp_bst.head = candidate;
		insert_bst(&temp_bst, b);
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

bst_node *bst_node_parent(bst_node *node) {
	return node->parent;
}


static void insert(bst_node *node, bst_node *newnode, comp_fn_t comp) {
	bst_node *left = node->left;
	bst_node *right = node->right;
	
	int compres = comp(newnode->data, node->data);
	if (compres < 0)
		if (left == NULL) {
			node->left = newnode;
			newnode->parent = node;
		}
		else
			insert(left, newnode, comp);
	else if (compres > 0)
		if (right == NULL) {
			node->right = newnode;
			newnode->parent = node;
		}
		else
			insert(right, newnode, comp);
	else
		node->count++;
}

static bst_node *search(bst_node *node, void *elem_addr, comp_fn_t comp) {
	if (node == NULL)
		return NULL;
	int compres = comp(node->data, elem_addr);
	if ( compres == 0)
		return node; // found
	if (compres > 0)
		return search(node->left, elem_addr, comp);
	return search(node->right, elem_addr, comp);
}

static bst_node *search_node(bst *b, void *elem_addr, comp_fn_t comp_param) {
	bst_node *root = b->head;
	comp_fn_t comp = comp_param == NULL ? b->comp : comp_param;

	return search(root, elem_addr, comp);
}

static void visit_insert(void *elem_addr, bst *b) {
	/* Already have an insert function but with switched params. */
	bst_insert(b, elem_addr);
}

static void insert_bst(bst *from, bst *to) {
	/* Traverse the tree, adding each found node in the destination tree.*/
	bst_traverse_breadth_first(from, (bst_visit_fn_t)visit_insert, to);
}

static bst_node *new_node(size_t tsize, void *elem_addr) {
	bst_node *newnode = malloc(sizeof(bst_node));

	if (newnode == NULL)
		return NULL;
	if ((newnode->data = malloc(tsize)) == NULL)
		return NULL;

	memcpy(newnode->data, elem_addr, tsize);
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	newnode->count = 1;
	return newnode;
}

static void traverse_inorder_visit_node(bst_node *node,
				bst_visit_fn_t visit,
				void *obj) {
	if (node == NULL)
		return;
	traverse_inorder_visit_node(node->left, visit, obj);
	visit(node, obj);
	traverse_inorder_visit_node(node->right, visit, obj);
}

static void traverse_inorder_visit_node_data(bst_node *node,
				       bst_visit_fn_t visit,
				       void *obj) {
	if (node == NULL)
		return;
	traverse_inorder_visit_node_data(node->left, visit, obj);
	visit(node->data, obj);
	traverse_inorder_visit_node_data(node->right, visit, obj);
}

static void visit_count(bst_node *node, int *res) {
	*res += node->count;
}

static void traverse_preorder(bst_node *node,
			      bst_visit_fn_t visit,
			      void *obj) {
	if (node == NULL)
		return;

	visit(node->data, obj);
	traverse_preorder(node->left, visit, obj);
	traverse_preorder(node->right, visit, obj);
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

static bst_node *fill_find_node(bst_node *node,
				bst_check_fill_fn_t check_fill,
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
