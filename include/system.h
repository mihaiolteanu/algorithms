#include <stdbool.h>

#define OK 1
#define ERROR 0

/* Comparison function type. 
   The funtion should return an integer less than, equal to, or greater than 
   zero if a is found, respectively, to be less than, to mach, or be greater
   than b (same semantics as strcmp, for example) */
typedef	int (*comp_fn_t)(const void *a, const void *b);
