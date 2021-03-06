#include "bbst.h"
#include "array.h"
#include "common_int_member.h"
#include "unity.h"

static void node_visit(int *visited, array *a) {
	array_add(a, visited);
}

void test_bbst_balancing() {
	bbst bb;
	bst *b = &bb.b;
	size_t size = 7;
	/* Collect the elements from the bst after insertion into an array. */
	array a;

	bbst_init(&bb, sizeof(int), comp_int_member);
	array_init(&a, sizeof(int), NULL);
	/* Insert 1, 2, 3, 4, 5, 6, 7 into the tree. */
	for (int i = 1; i < size+1; i++)
		bbst_insert(&bb, &i);
	/* The balanced tree should look like:
	                  4
                        /   \
                      2      6
                    /  \    / \
                   1   3   5   7
	*/

	bst_traverse_breadth_first(b, (bst_visit_fn_t)node_visit, &a);

	/* After breadth first traversal, the collected values should be: */
	int expected[] = {4, 2, 6, 1, 3, 5, 7};

	for (int i = 0; i < size; i++) {
		int *value = (int *)array_value(&a, i);
		TEST_ASSERT_EQUAL_INT(*value, expected[i]);
	}
}

void test_bbst_search() {
	bbst bb;
	int ints[] = {5, 3, 7, 4, 2, 3};
	int ints_size = ARRAY_SIZE(ints);

	bbst_init(&bb, sizeof(int), comp_int_member);
	insert_ints(&bb, (add_fn_t)bbst_insert, ints, ints_size);
	assert_ints(&bb, (search_fn_t)bbst_search, ints, ints_size);
}
