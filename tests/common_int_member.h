/* common_int_member.h - Functions and utilities for handling an int member in 
   the different data structures. Used for testing. */

#ifndef COMMON_INT_MEMBER
#define COMMON_INT_MEMBER

typedef void (*add_fn_t)(void *data_type, void *elem_addr);

/* Comparison function for int members. */
extern int comp_int_member(const void *a, const void *b);
/* Insert all the ints into the data type using the add function. */
extern void insert_ints(void *data_type, add_fn_t add_fn, int *ints, int count);

#endif // COMMON_INT_MEMBER
