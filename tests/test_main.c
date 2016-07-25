#include <stdio.h>
#include "test_main.h"

int main(void) {
	run_all_array_tests();
	run_all_sarray_tests();
	run_all_queue_tests();
	run_all_stack_tests();
	run_all_dict_tests();
	run_all_bst_tests();
	run_all_bbst_tests();
 	run_all_list_tests();
	run_all_hash_tests();

	run_all_e_03_tests();

/* http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c */
	printf("\n\x1b[32m All tests passed \x1b[0m\n\n");
	return 0;
}
