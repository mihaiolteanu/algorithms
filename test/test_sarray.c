#include "sarray.h"
#include "common_int_member.h"
#include "unity.h"

void test_sarray_size() {
	sarray as;
	sarray_init(&as, sizeof(int), comp_int_member);

	// No elements added yet.
	TEST_ASSERT_EQUAL_INT(sarray_size(&as), 0);
	
	// Adding elements correctly resizes the array.
	size_t asize = 5;
	for (int i = 0; i < asize; i++) {
		sarray_add(&as, &i);
		TEST_ASSERT_EQUAL_INT(sarray_size(&as), i+1);
	}

	// Removing elements correctly resizes the array.
	for (size_t i = asize; i > 0; i--) {
		sarray_remove_byindex(&as, 0);
		TEST_ASSERT_EQUAL_INT(sarray_size(&as), i-1);
	}

	// Removing from an empty array doesn't change the size
	sarray_remove_byindex(&as, 0);
	TEST_ASSERT_EQUAL_INT(sarray_size(&as), 0);
}

void test_sarray_value() {
	sarray as;
	sarray_init(&as, sizeof(int), comp_int_member);

	// [5]
	int new_elem = 5;
	sarray_add(&as, &new_elem);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 0), new_elem);

	// To be added at index zero and shifting the previous zero index
	// value to index 1. --> [3 5]
	new_elem = 3;
	sarray_add(&as, &new_elem);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 0), 3);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 1), 5);

	// To be added at index one and shifting the previous one index
	// value to index 2. --> [3 4 5]
	new_elem = 4;
	sarray_add(&as, &new_elem);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 0), 3);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 1), 4);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 2), 5);

	// To be added at the end of the array, not modifying any of the
	// other indexes values. --> [3 4 5 7]
	new_elem = 7;
	sarray_add(&as, &new_elem);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 0), 3);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 1), 4);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 2), 5);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 3), 7);	
}

void test_sarray_remove_byindex() {
	sarray as;
	sarray_init(&as, sizeof(int), comp_int_member);

	for (int i = 0; i < 3; i++)
		sarray_add(&as, &i);

	// [0 1 2]
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 0), 0);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 1), 1);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 2), 2);

	// [0 2]
	sarray_remove_byindex(&as, 1);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 0), 0);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 1), 2);

	// [2]
	sarray_remove_byindex(&as, 0);
	TEST_ASSERT_EQUAL_INT(*(int *)sarray_value(&as, 0), 2);
}
