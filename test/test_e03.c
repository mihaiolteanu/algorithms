#include "e03.h"
#include "bst.h"
#include "list.h"
#include "common_int_member.h"
#include "unity.h"

void test_e03_01() {
    char *parens;
    int expect;

    struct {
	char *parens;
	int   expect;
    } pair[] = {
	{"((()))"	, 0},
	{"((())"	, 5},
	{"(()"		, 3},
	{""		, 0},
	{"("		, 1},
	{")"		, 1},
	{NULL		, -1}
    };

    int samples = sizeof(pair)/sizeof(pair[0]);
    for (int i=0; i<samples; i++) {
	parens = pair[i].parens;
	expect = pair[i].expect;
	TEST_ASSERT_EQUAL_INT(e03_01(parens), expect);
    }
}

void test_e03_02() {
    list l;
    list_node *node;
    int value;
    int array[5] = {1, 2, 3, 4, 5};

    list_init(&l, sizeof(int), comp_int_member);
    for (int i = 0; i < 5; i++)	/* Elements are added in reverse order. */
	list_add(&l, &array[i]);
    e03_02(&l);                 /* Reverse the list, obtaining the original array. */
    node = list_first_node(&l);
    for (int i = 0; i < 5; i++) {
        value = *(int *)list_node_data(node);
	TEST_ASSERT_EQUAL_INT(array[i], value);
	node = list_next_node(node);
    }
    list_destroy(&l);
}

void test_e03_10_best_fit() {
	int res;

	res = e_03_10_best_fit(10, 3, 6, 2, 1, 5, 7, 2, 4, 1, 9);

	/*
	  |3     |6    |2    |1     |5     |7      |2       |4      |1     |9
	  3      9     9     10     10     10      10       10      10(2)  10(2)
                      /     /      /      /       /        /       /      /
                     2     2      7      7(2)    7        7       7      7
                                                  \      / \     /      / \
                                                   9    4   9   4      4   9
	*/
	TEST_ASSERT_EQUAL_INT(res, 5);
}
	
void test_e03_11_a() {
	int res;

	res = e_03_11_a(1, 4,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 3 - 7 */
	TEST_ASSERT_EQUAL_INT(res, 1);

	res = e_03_11_a(4, 7,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 7 - 4 */
	TEST_ASSERT_EQUAL_INT(res, 2);

	res = e_03_11_a(2, 2,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 9 - 9 */
	TEST_ASSERT_EQUAL_INT(res, 9);
}

void test_e03_11_b() {
	int res;

	res = e_03_11_b(1, 4,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 3 - 7 */
	TEST_ASSERT_EQUAL_INT(res, 1);

	res = e_03_11_b(4, 7,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 7 - 4 */
	TEST_ASSERT_EQUAL_INT(res, 2);

	res = e_03_11_b(2, 2,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 9 - 9 */
	TEST_ASSERT_EQUAL_INT(res, 9);
}

void test_e03_13() {
	bst b;
	int count = 6;

	e_03_13_init(&b, count,
		     3, 5, 1, 9, 4, 2);
	int expected[] = {3, 8, 9, 18, 22, 24};

	/* Add to each position and retest the partial sum for each such
	   addition. */
	int to_add = 2;
	for (int i = 0; i < count; i++) {
		/* Test the partial sum. */
		for (int j = 0; j < count; j++) {
			int part_sum = e_03_13_partial_sum(&b, j);
			TEST_ASSERT_EQUAL_INT(part_sum, expected[j]);
		}
		e_03_13_add(&b, to_add, i);
		for (int j = i; j < count; j++)
			expected[j] += to_add;
	}
}

