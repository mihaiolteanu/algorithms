#include <stdio.h>
#include "test_main.h"

int main(void) {
	run_all_array_tests();
	run_all_array_sorted_tests();

	printf("-----------------\n\n");
	printf("All array tests passed\n");
	printf("All sorted array tests passed\n");

	return 0;
}
