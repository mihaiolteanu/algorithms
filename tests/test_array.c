#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include "array.h"
#include "common_int_member.h"

// Test functions
static void test_array_size();
static void test_array_value();
static void test_array_search();
static void test_array_remove_byindex();
static void test_array_add_at_index();

/* Assert that the count number of ints are not in the array. */
static void assert_ints_null(array *a, int *ints, int count);

void run_all_array_tests() {
	test_array_size();
	test_array_value();
	test_array_search();
	test_array_remove_byindex();
	test_array_add_at_index();
}

static void test_array_search() {
	array a;
	/* Expected values, used for both insertion and assertion. */
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);
	/* Values that should not be found in the array. */
	int not_exp[] = {4, 9, 12};
	int not_exp_size = ARRAY_SIZE(not_exp);

	array_init(&a, sizeof(int), comp_int_member);
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);

	/* Search existing and non-existing elements. */
	assert_ints(&a, (search_fn_t)array_search, ints, ints_size);
	assert_ints_null(&a, not_exp, not_exp_size);
}

static void test_array_add_at_index() {
	array a;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);

	/* Add elements at specific indexes - expected array. */
	int exp[] = {0, 2, 4, 5, 3, 10, 1, 11};
	/*           ^     ^               ^ */
	int exp_size = ARRAY_SIZE(exp);

	array_add_at_index(&a, &exp[0], 0); /* Start of array. */
	array_add_at_index(&a, &exp[2], 2);
	array_add_at_index(&a, &exp[7], 7); /* End of array. */
	assert_ints(&a, (search_fn_t)array_search, exp, exp_size);

	/* Add elements at non-existend index - should not be possible. */
	array_add_at_index(&a, &exp[0], ARRAY_SIZE(exp) + 2);
	/* The array has not been changed. */
	assert(array_size(&a) == ARRAY_SIZE(exp));
	assert_ints(&a, (search_fn_t)array_search, exp, exp_size);
}

static void test_array_remove_byindex() {
	array a;
	int ints[] = {2, 5, 3};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);

	// Removing from an empty array does not modify the array.
	assert(array_size(&a) == 0);
	array_remove_byindex(&a, 0);
	assert(array_size(&a) == 0);

	// Add 3 random elements to the array.
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);

	/* Remove the first element - check the array size and values. */
	assert(array_size(&a) == 3);
	array_remove_byindex(&a, 0);
	assert(array_size(&a) == 2);
	assert(*(int*)array_value(&a, 0) == 5);
	assert(*(int*)array_value(&a, 1) == 3);

	/* Remove an element at an index greater than the array size. */
	array_remove_byindex(&a, 2); 
	assert(array_size(&a) == 2);
	assert(*(int*)array_value(&a, 0) == 5);
	assert(*(int*)array_value(&a, 1) == 3);
}

static void test_array_size() {
	array a;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);
	/* Nothing added yet. */
	assert(array_size(&a) == 0);
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);
	assert(array_size(&a) == ints_size);
}

static void test_array_value() {
	array a;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);

	for  (int i = 0; i < ints_size; i++)
		assert(*(int *)array_value(&a, i) == ints[i]);
}

static void assert_ints_null(array *a, int *ints, int count) {
	for (int i = 0; i < count; i++) {
		int *res = array_search(a, &ints[i]);
		assert (res == NULL);
	}
}
