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
static void test_bst_traverse_breadth_first();
static void test_bst_fill();

/* ***** Helper functions ***** */
/* Traverse the bst in the order specified by the traverse function, collecting
 * all the node values into an array and then assert if the collected values 
 * match those given as arguments in the va_list. */
static void h_traverse_int_assert(bst *b,
		  void (*traverse)(bst *b, bst_visit_fn_t visit, void *obj),
		  int count, ...);

/* Adds the data to the array. Used as a node visit function for bst traversal*/
static void h_int_visit(void *data, array *a);

/* Insert count number of ints in the bst */
static void h_bst_insert_ints(bst *b, int count, ...);

void run_all_bst_tests() {
	test_bst_insert();
	test_bst_search();
	test_bst_search_count();
	test_bst_min_max();
	test_bst_traverse_inorder();
	test_bst_traverse_preorder();
	test_bst_traverse_breadth_first();
	test_bst_fill();
}

static int test_bst_check_fill(void *node_data, void *elem_addr) {
	int data = *(int*)node_data;
	int newval = *(int*)elem_addr;

	if (data+newval == 10)
		return 0;
	if (data+newval < 10)
		return -1;
	return 1;
}

/* Fill function */
static void h_bst_fill(void *node_data, void *elem_addr) {
	if (node_data != NULL)
		*(int*)node_data += *(int*)elem_addr;
}

static void test_bst_fill() {
	bst b;
	int fillval;

	bst_init(&b, sizeof(int), comp_int_member);

	/* Build the tree with five nodes:
	           5
		  / \
                 3   7
                / \
               2   4
	*/
	h_bst_insert_ints(&b, 5,
			  5, 3, 7, 4, 2);


	/* Fill at 3.
	          5
                 / \
                2   7
                 \   \
                  4  10
	*/
	fillval = 7;
	bst_fill(&b, test_bst_check_fill, h_bst_fill, &fillval);
	h_traverse_int_assert(&b, bst_traverse_inorder,
			      5,  2, 4, 5, 7, 10);


	/* Fill at 4.
	          5
                 / \
                2   7
                     \
                     10(2)
	*/
	fillval = 6;
	bst_fill(&b, test_bst_check_fill, h_bst_fill, &fillval);
	h_traverse_int_assert(&b, bst_traverse_inorder,
			      4,  2, 5, 7, 10);
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

	bst_init(&b, sizeof(int), comp_int_member);
	h_bst_insert_ints(&b, 8,
			  5, 3, 7, 4, 2, 7, 7, 4);

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

/* The following test functions use the same tree, but traverses it in different
 * fashions. The visiting function adds the node data (an int) to a resizable
 * array. The traverse function decides in what order the nodes are visited. The
 * arguments to the assert function reflect the expected data of the visited
 * nodes based on the visiting order. 
	           5
		  / \
                 3   7
                / \
               2   4
*/
static void test_bst_traverse_inorder() {
	bst b;

	bst_init(&b, sizeof(int), comp_int_member);
	h_bst_insert_ints(&b, 5,
			  5, 3, 7, 4, 2);
	h_traverse_int_assert(&b, bst_traverse_inorder,
			      5,  2, 3, 4, 5, 7);
}

static void test_bst_traverse_preorder() {
	bst b;

	bst_init(&b, sizeof(int), comp_int_member);
	h_bst_insert_ints(&b, 5,
			  5, 3, 7, 4, 2);
	h_traverse_int_assert(&b, bst_traverse_preorder,
			      5,  5, 3, 2, 4, 7);
}

static void test_bst_traverse_breadth_first() {
	bst b;

	bst_init(&b, sizeof(int), comp_int_member);
	h_bst_insert_ints(&b, 5,
			  5, 3, 7, 4, 2);
	h_traverse_int_assert(&b, bst_traverse_breadth_first,
			      5,  5, 3, 7, 2, 4);
}

static void h_int_visit(void *data, array *a) {
	array_add(a, data);
}

static void h_traverse_int_assert(bst *b,
		  void (*traverse)(bst *b, bst_visit_fn_t visit, void *obj),
		  int count, ...) {
	va_list ap;
	array a;

	array_init(&a, sizeof(int));
	/* Collect the node values. */
	traverse(b, (bst_visit_fn_t)h_int_visit, &a);

	/* The collected node values should match the ones given as arguments to
	   this function */
	va_start(ap, count);
	for (int i = 0; i < count; i++)
		assert(*(int*)array_value(&a, i) == va_arg(ap, int));

	va_end(ap);
}

static void h_bst_insert_ints(bst *b, int count, ...) {
	va_list ap;
	int value;

	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		value = va_arg(ap, int);
		bst_insert(b, &value);
	}
	va_end(ap);
}
