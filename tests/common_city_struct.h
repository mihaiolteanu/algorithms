/* common_city_struct.h - A city structure and different functions to be used
   with it (init, comparison functions, etc.). Used for testing the generic 
   data structures as a member of those data structures.
*/
#ifndef COMMON_CITY_STRUCT_H
#define COMMON_CITY_STRUCT_H

#include <stddef.h>
#include "system.h"

typedef struct {
	size_t size; // Size of the city
	char *name;  // Name of the city
} city;

/* Comparison function. Compares cities by name. Used in the initialization
   of data structures that require a comparison function. */
//extern int comp_city_byname(const void *a, const void *b);
extern comp_fn_t comp_city_byname;

#endif // COMMON_CITY_STRUCT_H

