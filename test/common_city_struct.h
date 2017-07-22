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

/* List of cities to be added to the data structure of choice. */
#define CITIES_SB_CJ_AB_SIZE 3
extern city cities_sb_cj_ab[];

/* An add (or insert) function for an adt usually accepts the adt itself as the
   first argument and the address of the element to be added to the addt as the
   second. */
typedef int (*adt_add_fn_t)(void *adt, void *elem_addr);

/* Insert the list of cities into the abstract data type using the insert
   function provided by the implementation of that data type. */
extern void city_insert(void *adt,
			adt_add_fn_t adt_add,
			city *cities);

/* A search function for an adt usually accepts the adt itself as the first
   argument and the address of the element it searches for as the second.
   Therefore, we can have a generic function type for it. */
typedef void* (*adt_search_fn_t)(void *adt, void *elem_addr);

/* Search for a city in the data structure pointed by adt, using that ds
   search function, and assert that the found city size matches the expected
   size*/
extern void city_search_byname(void *adt,
			       adt_search_fn_t adt_search,
			       city *c, int exp_size);

#endif // COMMON_CITY_STRUCT_H

