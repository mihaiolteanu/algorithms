#include "bst.h"
#include "bbst.h"
#include "sarray.h"

/* Insert all the elements from the sorted array, from index m to index n
   into the bst. The sorted array elements are bst nodes. */
static void reinsert(bst *b, sarray *sa, size_t m, size_t n);

extern int bbst_init(bbst *bb, size_t elem_size, comp_fn_t comp) {
	bst *b = &bb->b;
	sarray *sa = &bb->sa;

	bst_init(b, elem_size, comp);
	sarray_init(sa, elem_size, comp);

	return 0;
}

int bbst_insert(bbst *bb, void *elem_addr) {
	bst *b = &bb->b;
	sarray *sa = &bb->sa;
	int sa_size;

	sarray_add(sa, elem_addr);
	bst_destroy(b);
	sa_size = sarray_size(sa);
	reinsert(b, sa, 0, sa_size-1);
}

static void reinsert(bst *b, sarray *sa, size_t m, size_t n) {
	if (m > n)
		return;

	size_t middle = (m + n) / 2;                /* Middle index */
	void *value = sarray_value(sa, middle);     /* Middle node */

	bst_insert(b, value);
	if (middle > 0)
		reinsert(b, sa, m, middle - 1);     /* Insert the left nodes */
	reinsert(b, sa, middle + 1, n);             /* Insert the right nodes */
}

void *bbst_search(bbst *bb, void *elem_addr) {
	bst *b = &bb->b;
	return bst_search(b, elem_addr);
}

void *bbst_min(bbst *bb) {
	bst *b = &bb->b;
	return bst_min(b);
}

void *bbst_max(bbst *bb) {
	bst *b = &bb->b;
	return bst_max(b);
}

void bbst_destroy(bbst *bb) {
	bst *b = &bb->b;
	sarray *sa = &bb->sa;

	/* Both bst and sarray are allocated on the caller side. */
	bst_destroy(b);
	sarray_destroy(sa);
}
