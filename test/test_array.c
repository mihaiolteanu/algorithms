#include "array.h"
#include "common_int_member.h"
#include "unity.h"

/* Assert that the count number of ints are not in the array. */
static void assert_ints_null(array *a, int *ints, int count);
/* Assert array values. */
static void assert_int_values(array *a, int *ints, int ints_size);

void test_array_search() {
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

void test_array_add_at_index() {
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
	TEST_ASSERT_EQUAL(array_size(&a), ARRAY_SIZE(exp));
	assert_ints(&a, (search_fn_t)array_search, exp, exp_size);
}

void test_array_remove_byindex() {
	array a;
	int ints[] = {2, 5, 3};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);

	// Removing from an empty array does not modify the array.
	TEST_ASSERT_EQUAL_INT(array_size(&a), 0);
	array_remove_byindex(&a, 0);
	TEST_ASSERT_EQUAL_INT(array_size(&a), 0);

	// Add 3 random elements to the array.
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);

	/* Remove the first element - check the array size and values. */
	TEST_ASSERT_EQUAL_INT(array_size(&a), 3);
	array_remove_byindex(&a, 0);
	TEST_ASSERT_EQUAL_INT(array_size(&a), 2);
	int exp[] = {5, 3};
	int exp_size = ARRAY_SIZE(exp);
	assert_int_values(&a, exp, exp_size);

	/* Remove an element at an index greater than the array size. */
	array_remove_byindex(&a, 2);
	TEST_ASSERT_EQUAL_INT(array_size(&a), 2);
	assert_int_values(&a, exp, exp_size);
}

void test_array_size() {
	array a;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);
	/* Nothing added yet. */
	TEST_ASSERT_EQUAL_INT(array_size(&a), 0);
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);
	TEST_ASSERT_EQUAL_INT(array_size(&a), ints_size);
}

void test_array_value() {
	array a;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);
	assert_int_values(&a, ints, ints_size);
}

void test_array_expand_fill() {
	array a;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);

	array_init(&a, sizeof(int), comp_int_member);
	insert_ints(&a, (add_fn_t)array_add, ints, ints_size);

	/* Expand with enough elements to force a capacity increase of the
	 * array. */
	int exp[] = {2, 5, 3, 10, 1, 10, 10, 10, 10, 10, 10};
	int exp_size = ARRAY_SIZE(exp);
	int fill = 10;
	array_expand_fill(&a, 10, &fill);
	assert_int_values(&a, exp, exp_size);

	/* Expand only one element - boundary test */
	int exp1[] = {2, 5, 3, 10, 1, 10, 10, 10, 10, 10, 10, 25};
	exp_size = ARRAY_SIZE(exp1);
	fill = 25;
	array_expand_fill(&a, 11, &fill);
	assert_int_values(&a, exp1, exp_size);
}

void test_array_expand_fill_empty_array() {
	array a;
	int exp[] = {5, 5, 5, 5, 5};
	int exp_size = ARRAY_SIZE(exp);
	int fill = 5;

	/* Do not insert any members, just expand the array. */
	array_init(&a, sizeof(int), comp_int_member);
	array_expand_fill(&a, 4, &fill);
	assert_int_values(&a, exp, exp_size);
}

static void assert_ints_null(array *a, int *ints, int count) {
	for (int i = 0; i < count; i++) {
		int *res = array_search(a, &ints[i]);
		TEST_ASSERT_NULL(res);               
	}
}

static void assert_int_values(array *a, int *ints, int ints_size) {
	for (int i = 0; i < ints_size; i++) {
		int *res = array_value(a, i);
		if (res != NULL)
		        TEST_ASSERT_EQUAL(*res, ints[i]);
		else if (ints[i] != 0) /* Value 0 can be mistaken with NULL. */
		        TEST_ASSERT_TRUE_MESSAGE(0, "Array value returned NULL");
	}
}
