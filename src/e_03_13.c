#include <stddef.h>
#include <stdarg.h>
#include "e_03.h"
#include "bst.h"

/* Store the sum for the interval [start, stop] in sum. */
typedef struct {
	size_t start;
	size_t stop;
	int sum;
} e_03_13_node;

/* Hackish. Direct access to the bst data structure. */
static int node_sum(bst_node *node) {
	return ((e_03_13_node*)node->data)->sum;
}

static int node_start(bst_node *node) {
	return ((e_03_13_node*)node->data)->start;
}

static int node_stop(bst_node *node) {
	return ((e_03_13_node*)node->data)->stop;
}

/* Comparison function for the bst. 
Sample tree resulting from bst insertion using this comparison function for 
the array [3, 5, 1, 9], if at each step we add half the array (similar to a
binary search algorithm):

                      18 [0, 3]
                     /         \
             8 [0, 1]           10 [2, 3]
            /        \         /         \
           3 [0, 0]  5[1, 1]  1[2, 2]    3[3, 3]

where the first value is the value from the above struct and the values between
[ and ] are start and stop, respectively. */
static int comp(const e_03_13_node *a, const e_03_13_node *b) {
	size_t a_sum = a->start + a->stop;
	size_t b_sum = b->start + b->stop;

	if ((a->stop < b->stop) && (a_sum <= b_sum))
		return -1;
	else
		return 1;
	/* Equal should not happen. */
}

/* Separate function used for bst search. */
static int search_comp(const e_03_13_node *a, const e_03_13_node *b) {
	size_t a_int_middle = (a->start + a->stop) / 2;
	size_t b_int_middle = (b->start + b->stop) / 2;

	if ((a->start == b->start) && (a->stop == b->stop))
		return 0;
	if ((a->start + a->stop) < (b->start + b->stop))
		return -1;
	return 1;
}

/* Add the collected values from the array in a bst with index as key.
 Split the array and add the middle element, then add the resulting left and
 right array (similar to a binary search procedure) thus keeping the tree
 balanced.*/
static void array_add_to_bst(int *array, int start, int stop, bst *b) {
	size_t middle = (start + stop) / 2;
	int sum = 0;

	/* Add a new node with the sum of the elements in the given interval. */
	/* Recalculating the sums over and over again. The requirements places
	no limit regarding the time complexity for building the data structure,
	so I'll leave it be as this is straightforward. */
	for (int i = start; i <= stop; i++)
		sum += array[i];
	e_03_13_node newnode =
		{.start = start, .stop = stop, .sum = sum};
	bst_insert(b, &newnode);

	/* Add the left and right subarrays. */
	if (start != stop) {
		array_add_to_bst(array, start, middle, b);
		array_add_to_bst(array, middle + 1, stop, b);
	}
}

void e_03_13_init(bst *b, int count, ...) {
	va_list ap;
	int array[count];

	bst_init(b, sizeof(e_03_13_node), (comp_fn_t)comp);

	va_start(ap, count);	
	/* Collect the values in an array. */
	for (int i = 0; i < count; i++)
		array[i] = va_arg(ap, int);
	va_end(ap);

	array_add_to_bst(array, 0, count - 1, b);
}

/* Traverse the bst tree to find the sum from index 0 to index int_search. */
static int partial_sum(bst_node *node, size_t int_search) {
	size_t start = node_start(node);
	size_t stop = node_stop(node);
	size_t int_middle = (start + stop) / 2;

	if (int_search < start)
		return 0;
	if (int_search >= stop)
		return node_sum(node);
	if (int_middle == start)
		return node_sum(node->left);
	if (int_middle <= int_search)
		return node_sum(node->left) + partial_sum(node->right, int_search);
	if (int_middle > int_search)
		return partial_sum(node->left, int_search);

	return 0;
}

int e_03_13_partial_sum(bst *b, int n) {
	/* Hackish. The comparison function does not help us in finding the
	sum in this case. Maybe I should have modified the bst
	implementation to add another interface to handle this. */
	bst_node *node = b->head;

	return partial_sum(node, n);
}

void e_03_13_add(bst *b, int y, int n) {
	/* Search for a leaf node (a node with same start and stop.) */
	e_03_13_node node = {.start = n, .stop = n, .sum = -1};
	bst_node *res = bst_search_with_comp(b, &node, search_comp);

	/* Add the new value to the node itself and to all of its parents. */
	while (res != NULL) {
		e_03_13_node *node = res->data;
		node->sum += y;
		res = bst_node_parent(res);
	}
}
