#include "bst.h"
#include "bbst.h"
#include "sarray.h"

/* Insert all the elements from the sorted array, from index m to index n
   into the bst with node as root. */
static void reinsert(bbst *bb, bst *b, sarray *sa, size_t m, size_t n);

extern int bbst_init(bbst *bb, size_t elem_size,
		     comp_fn_t comp,
		     comp_fn_t node_comp) {
	bst *b = &bb->b;
	sarray *sa = &bb->sa;
	bb->node_comp = node_comp;

	bst_init(b, elem_size, comp);
	sarray_init(sa, sizeof(bst_node) + sizeof(int), node_comp);

	return 0;
}

int bbst_insert(bbst *bb, void *elem_addr) {
	bst *b = &bb->b;
	bst_node *head = b->head;
	bst_node *node;
	sarray *sa = &bb->sa;

	node = bst_insert(b, elem_addr);
	/* The data stored in the sorted array is the whole bst node. */
	sarray_add(sa, node);
	if (head != NULL) {
		/* Reinsert all the elements from the sorted array back into the
		 * bst to keep the tree balanced. */
		b->head = NULL;
		int sa_size = sarray_size(sa);
		reinsert(bb, b, sa, 0, sa_size-1);
	}
	else
		; /* This was the first element, so nothing to do. */
}

static void reinsert(bbst *bb, bst *b, sarray *sa, size_t m, size_t n) {
	if (m > n)
		return;

	size_t middle_index = (m + n) / 2;
	bst_node *middle_node = sarray_value(sa, middle_index);

	middle_node->left = middle_node->right = NULL;
	bst_insert_node(b, middle_node, bb->node_comp);
	if (middle_index > 0)
		reinsert(bb, b, sa, m, middle_index - 1); /* Insert the left. */
	reinsert(bb, b, sa, middle_index + 1, n); /* Insert the right. */
}
