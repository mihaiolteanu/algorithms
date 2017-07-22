#include <assert.h>
#include "e_03.h"
#include "bst.h"

static void test_e_03_10_best_fit();
static void test_e_03_11_a();
static void test_e_03_11_b();
static void test_e_03_13();

void run_all_e_03_tests() {
	test_e_03_10_best_fit();
	test_e_03_11_a();
	test_e_03_11_b();
	test_e_03_13();
}

static void test_e_03_10_best_fit() {
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
	assert(res == 5);
}
	
static void test_e_03_11_a() {
	int res;

	res = e_03_11_a(1, 4,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 3 - 7 */
	assert(res == 1);

	res = e_03_11_a(4, 7,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 7 - 4 */
	assert(res == 2);

	res = e_03_11_a(2, 2,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 9 - 9 */
	assert(res == 9);
}

static void test_e_03_11_b() {
	int res;

	res = e_03_11_b(1, 4,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 3 - 7 */
	assert(res == 1);

	res = e_03_11_b(4, 7,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 7 - 4 */
	assert(res == 2);

	res = e_03_11_b(2, 2,  8,
			5, 3, 9, 1, 7, 2, 3, 4); /* 9 - 9 */
	assert(res == 9);
}

static void test_e_03_13() {
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
			assert(part_sum == expected[j]);
		}
		e_03_13_add(&b, to_add, i);
		for (int j = i; j < count; j++)
			expected[j] += to_add;
	}
}

