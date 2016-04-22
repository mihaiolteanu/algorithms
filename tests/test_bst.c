/* test_bst.c - Tests for the generic binary search tree
 */

#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "bst.h"
#include "common_city_struct.h"
#include "common_int_member.h"
#include "array.h"

// ***** Test functions *****
static void test_bst_insert();
static void test_bst_search();
static void test_bst_search_count();
static void test_bst_min_max();
static void test_bst_traverse_inorder();
static void test_bst_traverse_preorder();

void run_all_bst_tests() {
	test_bst_insert();
	test_bst_search();
	test_bst_search_count();
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
	city_insert(&b, (adt_add_fn_t)bst_insert, cities_sb_cj_ab);

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
	city_insert(&b, (adt_add_fn_t)bst_insert, cities_sb_cj_ab);

	// All cities must be included in the tree.
	for(int i = 0; i < CITIES_SB_CJ_AB_SIZE; i++)
		city_search_byname(&b, (adt_search_fn_t)bst_search,
				   &cities_sb_cj_ab[i],
				   cities_sb_cj_ab[i].size);

}

static void test_bst_search_count() {
	bst b;
	int search_elem, search_res;
	int node_values[] = {5, 3, 7, 4, 2, 7, 7, 4};

	bst_init(&b, sizeof(int), comp_int_member);

	// Insert some nodes
	for (int i = 0; i < sizeof(node_values)/sizeof(node_values[0]); i++)
		bst_insert(&b, &(node_values[i]));

	search_elem = 7;
	search_res = bst_search_count(&b, &search_elem);
	assert(search_res == 3); // We've added three nodes with value 7.

	search_elem = 4;
	search_res = bst_search_count(&b, &search_elem);
	assert(search_res == 2); // We've added three nodes with value 4.

	search_elem = 5;
	search_res = bst_search_count(&b, &search_elem);
	assert(search_res == 1); // We've added one node with value 5.
}

static void test_bst_min_max() {
	bst b;
	city *c;

	bst_init(&b, sizeof(city), comp_city_byname);

	// Insert some cities.
	city_insert(&b, (adt_add_fn_t)bst_insert, cities_sb_cj_ab);

	c = bst_min(&b);
	assert(strcmp(c->name, "alba") == 0);

	c = bst_max(&b);
	assert(strcmp(c->name, "sibiu") == 0);
}

/* Each node visit adds the node data to the array. */
void int_visit(void *data, array *a) {
	array_add(a, data);
}

/* Traverse the bst in an in-order fashion, collecting all the node values into
 * an array and then assert if the collected values match those given as
 * arguments in the va_list. */
static h_traverse_inorder_int_assert(bst *b, int count, ...) {
	va_list ap;
	array a;

	array_init(&a, sizeof(int));
	/* Collect the node values inorder in the array a */
	bst_traverse_inorder(b, (bst_visit_fn_t)int_visit, &a);

	/* The collected node values should match the ones given as arguments to
	   this function */
	va_start(ap, count);
	for (int i = 0; i < count; i++)
		assert(*(int*)array_value(&a, i) == va_arg(ap, int));

	va_end(ap);
}

static void test_bst_traverse_inorder() {
	bst b;
	// The values to be added in the bst
	int node_values[] = {5, 3, 7, 4, 2};
	// And then visit and collect each node data in an array.
	array a;
	array_init(&a, sizeof(int));
	bst_init(&b, sizeof(int), comp_int_member);
	
	/* Build the tree:
	           5
		  / \
                 3   7
                / \
               2   4
	*/
	for (int i = 0; i < sizeof(node_values)/sizeof(node_values[0]); i++)
		bst_insert(&b, &(node_values[i]));

	h_traverse_inorder_int_assert(&b, 5, 2, 3, 4, 5, 7);
}

static void test_bst_traverse_preorder() {
	bst b;
	// The values to be added in the bst
	int node_values[] = {5, 3, 7, 4, 2};
	// And then visit and collect each node data in an array.
	array a;
	array_init(&a, sizeof(int));
	bst_init(&b, sizeof(int), comp_int_member);
	
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
	bst_traverse_preorder(&b, (bst_visit_fn_t)int_visit, &a);
	assert(*(int*)array_value(&a, 0) == 5);
	assert(*(int*)array_value(&a, 1) == 3);
	assert(*(int*)array_value(&a, 2) == 2);
	assert(*(int*)array_value(&a, 3) == 4);
	assert(*(int*)array_value(&a, 4) == 7);
}
