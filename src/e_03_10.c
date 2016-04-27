#include <stdarg.h>
//#include <stdlib.h>
#include "bst.h"

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
