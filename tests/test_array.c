#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include "array.h"
#include "common_int_member.h"

// Test functions
static void test_array_size();
static void test_array_value();
static void test_array_capacity();
static void test_array_search();
static void test_array_remove_byindex();
static void test_array_add_at_index();

/* Add n elements to the array a */
static void add_elements(array *a, size_t n);
/* Assert that the count number of ints are not in the array. */
static void assert_ints_null(array *a, int *ints, int count);

void run_all_array_tests() {
	test_array_size();
	test_array_value();
	test_array_capacity();
	test_array_search();
	test_array_remove_byindex();
	test_array_add_at_index();
}

static void test_array_search() {
	array a;
	/* Expected values, used for both insertion and assertion. */
	int exp[] = {2, 5, 3, 10, 1}; 
	/* Values that should not be found in the array. */
	int not_exp[] = {4, 9, 12};

	array_init(&a, sizeof(int), comp_int_member);
	insert_ints(&a, (add_fn_t)array_add, exp, ARRAY_SIZE(exp));

	/* Search existing and non-existing elements. */
	assert_ints(&a, (search_fn_t)array_search, exp, ARRAY_SIZE(exp));
	assert_ints_null(&a, not_exp, ARRAY_SIZE(not_exp));
}

static void test_array_add_at_index() {
	array a;
	/* Initial elements added to the array. */
	int init[] = {2, 5, 3, 10, 1};

	array_init(&a, sizeof(int), comp_int_member);
	insert_ints(&a, (add_fn_t)array_add, init, ARRAY_SIZE(init));

	/* Add elements at specific indexes. */
	int exp[] = {0, 2, 4, 5, 3, 10, 1, 11};
	/*           ^     ^               ^ */
	array_add_at_index(&a, &exp[0], 0); /* Start of array. */
	array_add_at_index(&a, &exp[2], 2);
	array_add_at_index(&a, &exp[7], 7); /* End of array. */
	assert_ints(&a, (search_fn_t)array_search, exp, ARRAY_SIZE(exp));

	/* Add elements at non-existend index - should not be possible. */
	array_add_at_index(&a, &exp[0], ARRAY_SIZE(exp) + 2);
	/* The array has not been changed. */
	assert(array_size(&a) == ARRAY_SIZE(exp));
}

static void test_array_remove_byindex() {
	array a;
	array_init(&a, sizeof(int), comp_int_member);

	// Removing from an empty array does not modify the array.
	assert(array_size(&a) == 0);
	array_remove_byindex(&a, 0);
	assert(array_size(&a) == 0);

	// Add 3 random elements to the array.
	add_elements(&a, 3);

	// Removing an element decreases the size of the array by one.
	assert(array_size(&a) == 3);
	array_remove_byindex(&a, 0);
	assert(array_size(&a) == 2);

	// Removing an element at an index greater than the size does not
	// modify the array.
	// Index starts at zero, so this is > size
	array_remove_byindex(&a, 2); 
	assert(array_size(&a) == 2);
}

static void test_array_capacity() {
	array a;
	array_init(&a, sizeof(int), comp_int_member);

	// Initial capacity as expected?
	assert(array_cap(&a) == INIT_CAP);

	// Does the capacity double if the array is full?
	add_elements(&a, INIT_CAP + 1);
	assert(array_cap(&a) == 2*INIT_CAP);

	// Does the capacity shrinks if the array is half-full?
	array_remove_byindex(&a, 0);
	array_remove_byindex(&a, 0);
	assert(array_cap(&a) == INIT_CAP);
}

static void test_array_size() {
	array a;
	size_t asize = 3;
	array_init(&a, sizeof(int), comp_int_member);

	// Nothing added yet
	assert(array_size(&a) == 0);

	// Add some elements
	add_elements(&a, asize);
	assert(array_size(&a) == asize);
}

static void test_array_value() {
	array a;
	size_t asize = 3;
	array_init(&a, sizeof(int), comp_int_member);

	// Check if elements are added at the expected position
	add_elements(&a, asize);

	for  (int i = 0; i < asize; i++)
		assert(*(int *)array_value(&a, i) == i);
}


static void add_elements(array *a, size_t n) {
	for (int i = 0; i < n; i++)
		array_add(a, &i);
}

static void assert_ints_null(array *a, int *ints, int count) {
	for (int i = 0; i < count; i++) {
		int *res = array_search(a, &ints[i]);
		assert (res == NULL);
	}
}
