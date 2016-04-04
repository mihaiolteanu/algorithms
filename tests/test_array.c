#include <assert.h>
#include <stdio.h>
#include "array.h"

// Test functions
static void test_array_size();
static void test_array_value();
static void test_array_capacity();
static void test_array_remove_byindex();
static void test_array_add_at_index();

// Helper functions
// Add n elements to the array a
static void helper_array_add_elements(array *a, size_t n);

void run_all_array_tests() {
	test_array_size();
	test_array_value();
	test_array_capacity();
	test_array_remove_byindex();
	test_array_add_at_index();
}

static void helper_array_add_elements(array *a, size_t n) {
	for (int i = 0; i < n; i++)
		array_add(a, &i);
}

static void test_array_add_at_index() {
	array a;
	array_init(&a, sizeof(int));

	// 0 1 2 3
	helper_array_add_elements(&a, 4);

	// Add new element between 0 and 1
	int newelem = 5;
	array_add_at_index(&a, &newelem, 1);
	// Check correct adding and shifting of the rest of elements
	// leaving the rest of elements intact.
	// 0 5 1 2 3
	assert(*(int *)array_value(&a, 0) == 0);
	assert(*(int *)array_value(&a, 1) == 5);
	assert(*(int *)array_value(&a, 2) == 1);
	assert(*(int *)array_value(&a, 3) == 2);
	assert(*(int *)array_value(&a, 4) == 3);
}

static void test_array_remove_byindex() {
	array a;
	array_init(&a, sizeof(int));

	// Removing from an empty array does not modify the array.
	assert(array_size(&a) == 0);
	array_remove_byindex(&a, 0);
	assert(array_size(&a) == 0);

	// Add 3 random elements to the array.
	helper_array_add_elements(&a, 3);

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
	array_init(&a, sizeof(int));

	// Initial capacity as expected?
	assert(array_cap(&a) == INIT_CAP);

	// Does the capacity double if the array is full?
	helper_array_add_elements(&a, INIT_CAP + 1);
	assert(array_cap(&a) == 2*INIT_CAP);

	// Does the capacity shrinks if the array is half-full?
	array_remove_byindex(&a, 0);
	array_remove_byindex(&a, 0);
	assert(array_cap(&a) == INIT_CAP);
}

static void test_array_size() {
	array a;
	size_t asize = 3;
	array_init(&a, sizeof(int));

	// Nothing added yet
	assert(array_size(&a) == 0);

	// Add some elements
	helper_array_add_elements(&a, asize);
	assert(array_size(&a) == asize);
}

static void test_array_value() {
	array a;
	size_t asize = 3;
	array_init(&a, sizeof(int));

	// Check if elements are added at the expected position
	helper_array_add_elements(&a, asize);

	for  (int i = 0; i < asize; i++)
		assert(*(int *)array_value(&a, i) == i);
}
