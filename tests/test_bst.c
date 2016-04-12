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

void run_all_bst_tests() {
	test_bst_insert();
	test_bst_search();
	test_bst_min_max();
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
