#include <assert.h>
#include "e_03.h"

void run_all_e_03_tests() {
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
