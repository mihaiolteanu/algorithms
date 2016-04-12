/* test_bst.c - Tests for the generic binary search tree
 */

#include <assert.h>
#include <string.h>
#include "bst.h"
#include "common_city_struct.h"

// ***** Test functions *****
static void test_bst_insert();
static void test_bst_search();
static void test_bst_min_max();
static void test_bst_traverse_inorder();

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


/* Keep the data traversed in an array. */
#define INORDER_NODES 5
int inorder_values[INORDER_NODES];
int inorder_cur = 0;

/* Each node visit adds the node data to the array. */
void int_visit(void *data) {
	inorder_values[inorder_cur++] = *(int*)data;
}

static void test_bst_traverse_inorder() {
	bst b;

	/* Use a bst of ints */
	bst_init(&b, sizeof(int), intcomp);

	/* Build the tree:
	           3
		  / \
                 2   5
                / \
               1   4
	*/
	int node_values[INORDER_NODES] = {3, 2, 5, 4, 1};
	for (int i = 0; i < INORDER_NODES; i++)
		bst_insert(&b, &(node_values[i]));

	// Traverse the tree and collect the data: [1 2 3 4 5]
	bst_traverse_inorder(&b, int_visit);
	for(int i = 0; i < INORDER_NODES; i++)
		assert(inorder_values[i] == i + 1);
	
}
