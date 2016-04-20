/* test_array_sorted.c 
   Tests for the sorted generic array implementation
*/

#include <assert.h>
#include "array_sorted.h"
#include "common_int_member.h"

static void test_array_sorted_size(); 
static void test_array_sorted_value();
static void test_array_sorted_remove_byindex();


void run_all_array_sorted_tests() {
	test_array_sorted_size();  
	test_array_sorted_value(); 
	test_array_sorted_remove_byindex();
}

// Test functions

static void test_array_sorted_size() {
	array_sorted as;
	array_sorted_init(&as, sizeof(int), comp_int_member);

	// No elements added yet.
	assert(array_sorted_size(&as) == 0);
	
	// Adding elements correctly resizes the array.
	size_t asize = 5;
	for (int i = 0; i < asize; i++) {
		array_sorted_add(&as, &i);
		assert(array_sorted_size(&as) == i+1);
	}

	// Removing elements correctly resizes the array.
	for (size_t i = asize; i > 0; i--) {
		array_sorted_remove_byindex(&as, 0);
		assert(array_sorted_size(&as) == i-1);
	}

	// Removing from an empty array doesn't change the size
	array_sorted_remove_byindex(&as, 0);
	assert(array_sorted_size(&as) == 0);
}

static void test_array_sorted_value() {
	array_sorted as;
	array_sorted_init(&as, sizeof(int), comp_int_member);

	// [5]
	int new_elem = 5;
	array_sorted_add(&as, &new_elem);
	assert(*(int *)array_sorted_value(&as, 0) == new_elem);

	// To be added at index zero and shifting the previous zero index
	// value to index 1. --> [3 5]
	new_elem = 3;
	array_sorted_add(&as, &new_elem);
	assert(*(int *)array_sorted_value(&as, 0) == 3);
	assert(*(int *)array_sorted_value(&as, 1) == 5);

	// To be added at index one and shifting the previous one index
	// value to index 2. --> [3 5 5]
	new_elem = 5;
	array_sorted_add(&as, &new_elem);
	assert(*(int *)array_sorted_value(&as, 0) == 3);
	assert(*(int *)array_sorted_value(&as, 1) == 5);
	assert(*(int *)array_sorted_value(&as, 2) == 5);

	// To be added at the end of the array, not modifying any of the
	// other indexes values. --> [3 5 5 7]
	new_elem = 7;
	array_sorted_add(&as, &new_elem);
	assert(*(int *)array_sorted_value(&as, 0) == 3);
	assert(*(int *)array_sorted_value(&as, 1) == 5);
	assert(*(int *)array_sorted_value(&as, 2) == 5);
	assert(*(int *)array_sorted_value(&as, 3) == 7);	
}

static void test_array_sorted_remove_byindex() {
	array_sorted as;
	array_sorted_init(&as, sizeof(int), comp_int_member);

	for (int i = 0; i < 3; i++)
		array_sorted_add(&as, &i);

	// [0 1 2]
	assert(*(int *)array_sorted_value(&as, 0) == 0);
	assert(*(int *)array_sorted_value(&as, 1) == 1);
	assert(*(int *)array_sorted_value(&as, 2) == 2);

	// [0 2]
	array_sorted_remove_byindex(&as, 1);
	assert(*(int *)array_sorted_value(&as, 0) == 0);
	assert(*(int *)array_sorted_value(&as, 1) == 2);

	// [2]
	array_sorted_remove_byindex(&as, 0);
	assert(*(int *)array_sorted_value(&as, 0) == 2);
}
