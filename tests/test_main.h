#ifndef TESTS_MAIN_H
#define TESTS_MAIN_H

extern void run_all_array_tests();
extern void run_all_sarray_tests();
extern void run_all_queue_tests();
extern void run_all_stack_tests();
extern void run_all_dict_tests();
extern void run_all_bst_tests();
extern void run_all_bbst_tests();
extern void run_all_list_tests();

/* Exercises tests - maybe this should not form a part of the testing, but as
 * long as the implementation of the exercises is tested with the same method as
 * the unit tests (i.e. with asserts and not with printf and the like), why not
 * keep the tests and run them with all the other tests all the time?! Who
 * knows, maybe we'll catch something. */
extern void run_all_e_03_tests(); /* Chapter 3 exercises. */

#endif // TESTS_MAIN_H
