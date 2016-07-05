/* common_int_member.h - Functions and utilities for handling an int member in 
   the different data structures. Used for testing. */

#ifndef COMMON_INT_MEMBER
#define COMMON_INT_MEMBER

typedef void (*add_fn_t)(void *data_type, void *elem_addr);
typedef void *(*search_fn_t)(void *data_type, void *elem_addr);

/* Comparison function for int members. */
extern int comp_int_member(const void *a, const void *b);
/* Insert all the ints into the data type using the add function. */
extern void insert_ints(void *data_type, add_fn_t add_fn, int *ints, int count);
/* Search each memeber of the ints array in the data_type using the search
 * function. Asserts if the return value from the search function matches the
 * value from the ints array. */
extern void assert_ints(void *data_type, search_fn_t search_fn,
			int *ints, int count);

#endif // COMMON_INT_MEMBER
