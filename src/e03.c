#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "e03.h"
#include "stack.h"
#include "bst.h"

/* §§§ Exercise 03.01 */
void e_03_01(char *parens) {
	stack s;
	char c;
	int pos = 0;
	int res = stack_init(&s, sizeof(char));

	printf("%s\n", parens);

	while ((c = *parens++) != '\0' && ++pos) {
		if (c == '(')
			stack_push(&s, &c);
		else if (c == ')') {
			if (stack_size(&s) == 0) {
				printf("wrong parens at pos %d\n", pos);
				break;
			} else
				stack_pop(&s);
		}
		else {
			printf("wrong char, %c at %d\n", c, pos);
			break;
		}
	}
	int size = stack_size(&s);
	if (size > 0)
		printf("Unclosed parens at pos %d\n", size);
	stack_destroy(&s);
}

/* §§§ Exercise 03.04 */
/* 3-4. [3] Design a dictionary data structure in which search, insertion, and
deletion can all be processed in O(1) time in the worst case. You may assume
the set elements are integers drawn from a finite set 1, 2, .., n, and
initialization can take O(n) time. */
#define E03_04FREE 0
#define E03_04USED 1
#define E03_04RESET 0
#define E03_04SET 1

typedef struct {
	int size;
	int *a;
} e03_04dict;

static int e03_04dict_setreset_value(e03_04dict *d, int value, int setreset) {
	int *a = d->a;
	int size = d->size;

	if (value > size)
		return -1;
	a[value - 1] = setreset;
}

int e03_04dict_init(e03_04dict *d, int size) {
	d->a = calloc(size, sizeof(int));
	if (d->a == NULL)
		return -1;
	d->size = size;
	return 0;
}

// Returns FREE if not found, USED if found, -1 if no such index.
int e03_04dict_search(e03_04dict *d, int value) {
	int *a = d->a;
	int size = d->size;

	if (value > size)
		return -1;
	return a[value];
}

int e03_04dict_insert(e03_04dict *d, int value) {
	e03_04dict_setreset_value(d, value, E03_04SET);
}
	
int e03_04dict_delete(e03_04dict *d, int value) {
	e03_04dict_setreset_value(d, value, E03_04RESET);
}


/* §§§ Exercise 03.10 */
typedef struct {
	int cap;         /* Bucket capacity. */
	int fill;        /* Ocuppied units. */
} bucket;

static int comp_bucket(const void *a, const void *b) {
	int afill = ((bucket*)a)->fill;
	int bfill = ((bucket*)b)->fill;

	if (afill < bfill)
		return -1;
	return afill > bfill;
}

static void bucket_fill(bucket *b, bucket *newb) {
	b->fill += newb->fill;
}

static int bucket_check_fill(bucket *b, bucket *newb) {
	int fill = b->fill;
	int cap = b->cap;
	int weight = newb->fill;
	int newweight = fill + weight;

	if (newweight < cap)
		return -1; /* Underfill. */
	if (newweight == cap)
		return 0;  /* Perfect fill. */
	if (newweight > cap)
		return 1;  /* Overfill. */
}	

int e_03_10_best_fit(int nobjects, ...) {
	bst b;
	int weight;
	bucket new_bucket;

	new_bucket.cap = 10;
	// Init a binary tree of buckets.
	bst_init(&b, sizeof(bucket), comp_bucket);

	// Add a first, empty bucket.
	bucket bk = {.cap = 10, .fill = 0};
	bst_insert(&b, &bk);

	va_list ap;
	va_start(ap, nobjects);

	for (int i = 0; i < nobjects; i++) {
		weight = va_arg(ap, int);
		new_bucket.fill = weight;
		bst_fill(&b,
			 (bst_check_fill_fn_t)bucket_check_fill,
			 (bst_fill_fn_t)bucket_fill,
			 &new_bucket);
	}
	va_end(ap);

	return bst_count(&b);
}


/* §§§ Exercise 03.11 */
int e_03_11_a(int m, int n, int count, ...) {
	int matrix[count][count]; /* O(n2) space. */
	va_list ap;

	va_start(ap, count);

	/* Collect the values in the matrix diagonal. */
	for (int i = 0; i < count; i++) {
		int next = va_arg(ap, int);
		matrix[i][i] = next;
	}

	for (int row = 0; row < count; row++) {
		for (int col = row; col < count; col++) {
			if (col == row)
				continue;  /* Already the correct value. */
			/* The element in the previous row is the smallest one
			   until now. Replace it if the current is smaller. */
			if (matrix[col][col] < matrix[row][col-1])
				matrix[row][col] = matrix[col][col];
			else
				matrix[row][col] = matrix[row][col-1];
		}
	}

	/* Display the resulting matrix.
	#include <stdio.h>
	for (int row = 0; row < count; row++) {
		for (int i = 0; i < row; i++)
			printf("   ");
		for (int col = row; col < count; col++)
			printf("%d  ", matrix[row][col]);
		printf("\n");
	}
	*/
	
	return matrix[m][n]; /* O(1) answer */
}

/* ***** Solution for point (b) ***** */

typedef struct {
	int start; /* Start index. */
	int stop;  /* Stop index. */
	int value;  /* Value for the interval. */
} interval;

/* Comparison function is used only for inserting the interval into the tree in
 * this case. Another function, not in the bst implementation,  is used for
 * searching. */
static int interval_insert(const interval *inew,    /* interval to add/search.*/
			   const interval *inode) { /* interval from bst. */
	int newsum = inew->start + inew->stop;
	int nodesum = inode->start + inode->stop;

	if (newsum == nodesum)
		return 0; /* Same interval. */
	if (newsum > nodesum)
		return 1;
	if (newsum < nodesum)
		return -1;
}

/* Example usage to print the interval tree:
 * bst_traverse_breadth_first(&b, (bst_visit_fn_t)interval_visit_print, NULL);*/
static void interval_visit_print(interval *ivisited, void *ignored) {
	int start = ivisited->start;
	int stop = ivisited->stop;
	int value = ivisited->value;

	printf("[%d - %d]\n", start, stop, value);
}

/* Take the start-stop interval and halve it into smaller and smaller pieces
 * until the interval is only one element. Store the result in the given array.
 * Example for splitting the [0 - 7] interval, where start = 0, stop = 7. The
 * array index where the result is stored is in the form "x:" as seen below:
 * 0:[0 - 7] 
 * 1:[0 - 3]  2:[4 - 7] 
 * 3:[0 - 1]  4:[2 - 3]  5:[4 - 5]  6:[6 - 7] 
 * 7:[0 - 0]  8:[1 - 1]  9:[2 - 2] 10:[3 - 3] 
  11:[4 - 4] 12:[5 - 5] 13:[6 - 6] 14:[7 - 7] */
static void split_interval(interval interval_array[],
			   int start, int stop, 
			   int idx) {
	interval_array[idx].start = start;
	interval_array[idx].stop = stop;
	if (start == stop)
		return;
	int middle = (start + stop) / 2;
	split_interval(interval_array, start, middle, idx*2 + 1);    /* Left. */
	split_interval(interval_array, middle + 1, stop, idx*2 + 2); /* Right.*/
}

/* Find the minimum value in the interval [m, n]. */
static int find_min(int m, int n, bst_node *node) {
	interval *intv = (interval*)node->data;
	int start = intv->start;
	int stop = intv->stop;
	int middle = (start + stop) / 2;
	int value = intv->value;

	if (start == stop)
		return value;
	if ((m <= start) && (n >= stop))
		return value;

	if (n <= middle)
		return find_min(m, n, node->left);
	if (m > middle)
		return find_min(m, n, node->right);
	int min_left = find_min(m, n, node->left);
	int min_right = find_min(m, n, node->right);
	if (min_left < min_right)
		return min_left;
	return min_right;
}
		
int e_03_11_b(int m, int n, int count, ...) {
	bst b;
	va_list ap;
	int values[count];
	int nintervals = 2*count - 1;
	/* Create the necessary intervals, find the minimum value for each one,
	   and only then add them in the bst. */
	interval interval_array[nintervals];

	/* Collect the values. */
	va_start(ap, count);
	for (int i = 0; i < count; i++)
		values[i] = va_arg(ap, int);
	va_end(ap);

	bst_init(&b, sizeof(interval), (comp_fn_t)interval_insert);
	split_interval(interval_array, 0, count-1, 0);

	for (int i = 0; i < nintervals; i++) {
		int start = interval_array[i].start;
		int stop = interval_array[i].stop;
		int min = values[start];
		/* Find the minumum for this interval. */
		for (int i = start+1; i <= stop; i++)
			if (values[i] < min)
				min = values[i];
		interval_array[i].value = min;			

		/* All info now available. */
		bst_insert(&b, &interval_array[i]);
	}
/* Print the resulting interval tree. */
//bst_traverse_breadth_first(&b, (bst_visit_fn_t)interval_visit_print, NULL);
	return find_min(m, n, bst_getroot(&b));
}


/* §§§ Exercise 03.13 */
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
	bst_node *res = bst_search_with_comp(b, &node, (comp_fn_t)search_comp);

	/* Add the new value to the node itself and to all of its parents. */
	while (res != NULL) {
		e_03_13_node *node = (e_03_13_node*)res->data;
		node->sum += y;
		res = bst_node_parent(res);
	}
}
