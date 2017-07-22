#include <stdarg.h>
#include "bst.h"
#include "common_city_struct.h"
#include "common_int_member.h"
#include "array.h"
#include "unity.h"

/* ***** Helper functions ***** */
/* Traverse the bst in the order specified by the traverse function, collecting
 * all the node values into an array and then assert if the collected values 
 * match those given as arguments in the va_list. */
typedef void (*traverse_fn)(bst *b, bst_visit_fn_t visit, void *obj);
static void traverse_int_assert(bst *b, traverse_fn traverse, int count, ...);

/* Adds the data to the array. Used as a node visit function for bst traversal*/
static void int_visit(void *data, array *a);

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

void test_bst_fill() {
	bst b;
	int fillval;
	int ints[] = {5, 3, 7, 4, 2};
	int ints_size = ARRAY_SIZE(ints);

	bst_init(&b, sizeof(int), comp_int_member);

	/* Build the tree with five nodes:
	           5
		  / \
                 3   7
                / \
               2   4
	*/
	insert_ints(&b, (add_fn_t)bst_insert, ints, ints_size);

	/* Fill at 3.
	          5
                 / \
                2   7
                 \   \
                  4  10
	*/
	fillval = 7;
	bst_fill(&b, test_bst_check_fill, (bst_fill_fn_t)h_bst_fill, &fillval);
	traverse_int_assert(&b, bst_traverse_inorder,
			    5,  2, 4, 5, 7, 10);

	/* Fill at 4.
	          5
                 / \
                2   7
                     \
                     10(2)
	*/
	fillval = 6;
	bst_fill(&b, test_bst_check_fill, (bst_fill_fn_t)h_bst_fill, &fillval);
	traverse_int_assert(&b, bst_traverse_inorder,
			    4,  2, 5, 7, 10);
}

void test_bst_insert() {
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
	TEST_ASSERT_EQUAL_STRING(c->name, "sibiu");
	// sb right node is empty
	TEST_ASSERT_NULL(right);

	// Descend down the tree.
	node = left;
	left = bst_node_left(node);
	right = bst_node_right(node);
	c = bst_node_value(node);
	TEST_ASSERT_EQUAL_STRING(c->name, "cluj");
	// cj right node is empty
	TEST_ASSERT_NULL(right);

	// Descend down the tree.
	node = left;
	left = bst_node_left(node);
	right = bst_node_right(node);
	c = bst_node_value(node);
	TEST_ASSERT_EQUAL_STRING(c->name, "alba");

	// ab has no children
	TEST_ASSERT_NULL(left);
	TEST_ASSERT_NULL(right);
}

void test_bst_search() {
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

void test_bst_search_count() {
	bst b;
	int search_elem, search_res;
	int ints[] = {5, 3, 7, 4, 2, 7, 7, 4};
	int ints_size = ARRAY_SIZE(ints);

	bst_init(&b, sizeof(int), comp_int_member);
	insert_ints(&b, (add_fn_t)bst_insert, ints, ints_size);

	search_elem = 7;
	search_res = bst_search_count(&b, &search_elem);
	TEST_ASSERT_EQUAL_INT(search_res, 3); // We've added three nodes with value 7.

	search_elem = 4;
	search_res = bst_search_count(&b, &search_elem);
	TEST_ASSERT_EQUAL_INT(search_res, 2); // We've added three nodes with value 4.

	search_elem = 5;
	search_res = bst_search_count(&b, &search_elem);
	TEST_ASSERT_EQUAL_INT(search_res, 1); // We've added one node with value 5.
}

void test_bst_min_max() {
	bst b;
	city *c;

	bst_init(&b, sizeof(city), comp_city_byname);

	// Insert some cities.
	city_insert(&b, (adt_add_fn_t)bst_insert, cities_sb_cj_ab);

	c = bst_min(&b);
	TEST_ASSERT_EQUAL_STRING(c->name, "alba");
        
	c = bst_max(&b);
	TEST_ASSERT_EQUAL_STRING(c->name, "sibiu");       
}

void test_bst_count() {
	bst b;
	int count;
	int ints[] = {5, 3, 7, 4, 2, 3};
	int ints_size = ARRAY_SIZE(ints);

	bst_init(&b, sizeof(int), comp_int_member);
	insert_ints(&b, (add_fn_t)bst_insert, ints, ints_size);
	count = bst_count(&b);
	TEST_ASSERT_EQUAL_INT(count, 6);
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
void test_bst_traverse_inorder() {
	bst b;
	int ints[] = {5, 3, 7, 4, 2};
	int ints_size = ARRAY_SIZE(ints);

	bst_init(&b, sizeof(int), comp_int_member);
	insert_ints(&b, (add_fn_t)bst_insert, ints, ints_size);
	traverse_int_assert(&b, bst_traverse_inorder,
			    5,  2, 3, 4, 5, 7);
}

void test_bst_traverse_preorder() {
	bst b;
	int ints[] = {5, 3, 7, 4, 2};
	int ints_size = ARRAY_SIZE(ints);

	bst_init(&b, sizeof(int), comp_int_member);
	insert_ints(&b, (add_fn_t)bst_insert, ints, ints_size);
	traverse_int_assert(&b, bst_traverse_preorder,
			    5,  5, 3, 2, 4, 7);
}

void test_bst_traverse_breadth_first() {
	bst b;
	int ints[] = {5, 3, 7, 4, 2};
	int ints_size = ARRAY_SIZE(ints);

	bst_init(&b, sizeof(int), comp_int_member);
	insert_ints(&b, (add_fn_t)bst_insert, ints, ints_size);
	traverse_int_assert(&b, bst_traverse_breadth_first,
			    5,  5, 3, 7, 2, 4);
}

static void int_visit(void *data, array *a) {
	array_add(a, data);
}

static void traverse_int_assert(bst *b, traverse_fn traverse, int count, ...) {
	va_list ap;
	array a;

	array_init(&a, sizeof(int), comp_int_member);
	/* Collect the node values. */
	traverse(b, (bst_visit_fn_t)int_visit, &a);

	/* The collected node values should match the ones given as arguments to
	   this function */
	va_start(ap, count);
	for (int i = 0; i < count; i++)
	        TEST_ASSERT_EQUAL(*(int*)array_value(&a, i), va_arg(ap, int));

	va_end(ap);
}
