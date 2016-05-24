#include <stddef.h>
#include <stdarg.h>
#include "e_03.h"
#include "bst.h"

typedef struct {
	size_t index;
	int value;
} e_03_13_node;

static int comp(const e_03_13_node *a, const e_03_13_node *b) {
	if (a->index < b->index)
		return -1;
	if (a->index == b->index)
		return 0;
	if (a->index > b->index)
		return 1;
}

/* Add the collected values from the array in a bst with index as key.
 Split the array and add the middle element, then add the resulting left and
 right array (similar to a binary search procedure) thus keeping the tree
 balanced.*/
static void array_add_to_bst(e_03_13_node *array, int first, int last, bst *b) {
	int middle = (first + last) / 2;
	bst_insert(b, &array[middle]);
	if (middle != first)
		array_add_to_bst(array, first, middle - 1, b);
	if (middle != last)
		array_add_to_bst(array, middle + 1, last, b);
}

void e_03_13_init(bst *b, int count, ...) {
	va_list ap;
	e_03_13_node array[count];
	int sum = 0;

	bst_init(b, sizeof(e_03_13_node), (comp_fn_t)comp);

	va_start(ap, count);	
	/* Collect the values in an array. */
	for (int i = 0; i < count; i++) {
		sum += va_arg(ap, int);
		e_03_13_node node = {.index = i, .value = sum};
		array[i] = node;
	}
	va_end(ap);
	array_add_to_bst(array, 0, count - 1, b);
}

void e_03_13_add(bst *b, int y, int n) {

}

int e_03_13_partial_sum(bst *b, int n) {
	int ignored = 12345;
	e_03_13_node node = {.index = n, .value = ignored};
	e_03_13_node *res = bst_search(b, &node);
	if (res != NULL)
		return res->value;
	return 0;
}
