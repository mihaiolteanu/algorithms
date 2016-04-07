#include <stdio.h>
#include "test_main.h"

int main(void) {
	run_all_array_tests();
	run_all_array_sorted_tests();
	run_all_queue_tests();
	run_all_stack_tests();
	run_all_dict_tests();
	run_all_bst_tests();
	run_all_list_tests();

	printf("-----------------\n\n");
	printf("All array tests passed\n");
	printf("All sorted array tests passed\n");
	printf("All queue tests passed\n");
	printf("All stack tests passed\n");
	printf("All dictionary tests passed\n");
	printf("All binary search tree tests passed\n");
	printf("All linked list tests passed\n");

	return 0;
}
