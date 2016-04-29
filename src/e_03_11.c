#include <stdarg.h>
#include "bst.h"

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
