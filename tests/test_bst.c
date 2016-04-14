/* test_bst.c - Tests for the generic binary search tree
 */

#include <assert.h>
#include <string.h>
#include "bst.h"
#include "common_city_struct.h"
#include "array.h"

// ***** Test functions *****
static void test_bst_insert();
static void test_bst_search();
static void test_bst_min_max();
static void test_bst_traverse_inorder();
static void test_bst_traverse_preorder();

/* Comparison function for sorted array of ints. TODO: maybe move it to a
   separate module so that all test modules can use it?! */
static int intcomp(const void *a, const void *b) {
	int avalue = *(int *)a;
	int bvalue = *(int *)b;

	if (avalue < bvalue)
		return -1;
	return avalue > bvalue;
}

void run_all_bst_tests() {
	test_bst_insert();
	test_bst_search();
	test_bst_min_max();
	test_bst_traverse_inorder();
	test_bst_traverse_preorder();
}

static void test_bst_insert() {
	bst b;
	bst_node *node, *left, *right;
	city *c;

	bst_init(&b, sizeof(city), comp_city_byname);

	/* Insert some cities.
	          sb
                 /
		cj
	       /
	      ab
	*/
	city_insert(&b, bst_insert, cities_sb_cj_ab);

	// sb is the root.
	node = bst_getroot(&b);
	left = bst_node_left(node);
	right = bst_node_right(node);
	c = bst_node_value(node);
	assert(strcmp(c->name, "sibiu") == 0);
	// sb right node is empty
	assert(right == NULL);

	// Descend down the tree.
	node = left;
	left = bst_node_left(node);
	right = bst_node_right(node);
	c = bst_node_value(node);
	assert(strcmp(c->name, "cluj") == 0);
	// cj right node is empty
	assert(right == NULL);

	// Descend down the tree.
	node = left;
	left = bst_node_left(node);
	right = bst_node_right(node);
	c = bst_node_value(node);
	assert(strcmp(c->name, "alba") == 0);

	// ab has no children
	assert(left == NULL);
	assert(right == NULL);
}

static void test_bst_search() {
	bst b;
	bst_node *node, *left, *right;
	city *c;

	bst_init(&b, sizeof(city), comp_city_byname);

	// Insert some cities.
	city_insert(&b, bst_insert, cities_sb_cj_ab);

	// All cities must be included in the tree.
	for(int i = 0; i < CITIES_SB_CJ_AB_SIZE; i++)
		city_search_byname(&b, bst_search,
				   &cities_sb_cj_ab[i],
				   cities_sb_cj_ab[i].size);

}

static void test_bst_min_max() {
	bst b;
	city *c;
	
	// Insert some cities.
	city_insert(&b, bst_insert, cities_sb_cj_ab);

	c = bst_min(&b);
	assert(strcmp(c->name, "alba") == 0);

	c = bst_max(&b);
	assert(strcmp(c->name, "sibiu") == 0);
}

/* Each node visit adds the node data to the array. */
void int_visit(void *data, array *a) {
	array_add(a, data);
}

static void test_bst_traverse_inorder() {
	bst b;
	// The values to be added in the bst
	int node_values[] = {5, 3, 7, 4, 2};
	// And then visit and collect each node data in an array.
	array a;
	array_init(&a, sizeof(int));
	bst_init(&b, sizeof(int), intcomp);
	
	/* Build the tree:
	           5
		  / \
                 3   7
                / \
               2   4
	*/
	for (int i = 0; i < sizeof(node_values)/sizeof(node_values[0]); i++)
		bst_insert(&b, &(node_values[i]));

	// Traverse the tree and collect the data: [2 3 4 5 7]
	bst_traverse_inorder(&b, int_visit, &a);
	assert(*(int*)array_value(&a, 0) == 2);
	assert(*(int*)array_value(&a, 1) == 3);
	assert(*(int*)array_value(&a, 2) == 4);
	assert(*(int*)array_value(&a, 3) == 5);
	assert(*(int*)array_value(&a, 4) == 7);
}

static void test_bst_traverse_preorder() {
	bst b;
	// The values to be added in the bst
	int node_values[] = {5, 3, 7, 4, 2};
	// And then visit and collect each node data in an array.
	array a;
	array_init(&a, sizeof(int));
	bst_init(&b, sizeof(int), intcomp);
	
	/* Build the tree:
	           5
		  / \
                 3   7
                / \
               2   4
	*/
	for (int i = 0; i < sizeof(node_values)/sizeof(node_values[0]); i++)
		bst_insert(&b, &(node_values[i]));

	// Traverse the tree and collect the data: [5 3 2 4 7]
	bst_traverse_preorder(&b, int_visit, &a);
	assert(*(int*)array_value(&a, 0) == 5);
	assert(*(int*)array_value(&a, 1) == 3);
	assert(*(int*)array_value(&a, 2) == 2);
	assert(*(int*)array_value(&a, 3) == 4);
	assert(*(int*)array_value(&a, 4) == 7);
}
