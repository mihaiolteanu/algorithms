/* array.h 
   Implementation of a generic resizable array.
   
Example for a resizable int array, if casting all over the place
is not what you want:

#include "array.h"
static int array_int_init(array *a) {
	return array_init(a, sizeof(int));
}

static int array_int_add(array *a, int new) {
	return array_add(a, &new);
}

static int array_int_value(array *a, size_t index) {
	return *(int *)array_value(a, index);
}

*/

#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

// initial array capacity
#define INIT_CAP 4

// auto-resizable array structure
typedef struct {
	size_t size;  // number of elements currently in the array
	size_t cap;   // maximum number of elements allowed
	size_t tsize; // size of one data element
	char *data;   // array elements
} array;

/* Initialize the array with sizeof of one of the elements
that it will hold. Returns ERROR if array could not be initialized,
OK otherwise*/
extern int array_init(array *a, size_t elem_size);

/* Add the contents at the specified address, elem_address, to
the end of the array and increases the array size. The number of bytes 
copied depends on the elem_size the array was initialized with.
If the array is full, it doubles it's capacity. If the capacity
cannot be increased, return ERROR. Return OK otherwise.*/
extern int array_add(array *a, void *elem_addr);

/* Add the contents at the specified address, elem_address, to 
the array at the specified index and increase the array size. The
elements after the index will be shifted to the right to make room
for the new element. */
extern int array_add_at_index(array *a, void *elem_addr, size_t index);

/* Return the address of the index position in the array. If
the index is greater than the array size, or if the index is
negative, return NULL. The number of safely accesible bytes
at the return address is equal to the elem_size specified
when array_init was called. */
extern void *array_value(array *a, size_t index);

/* Search the array for the element at the elem_addr. Use the compare
function, comp, to decide the comparing algorithm. The comparison function 
must return an integer less than, equal to, or greater than zero if the first
argument is considered to be respectively less than, equal to, or greater
than the second. Returns the address of the found element in the array, NULL
otherwise.

Example comp function for a city struct, for searching a city with a given
size:
typedef struct {
	char *name;
	size_t size;
} city;

int citycomp(void *x, void *y) {
	city *xcity = (city *)x;
	city *ycity = (city *)y;
	size_t xsize = xcity->size;
	size_t ysize = ycity->size;

	if (xsize < ysize)
		return -1;
	return (xsize > ysize);
} */
extern void *array_search(array *a, void *elem_addr,
			  int (*comp)(void *x, void *y));

/* Remove element at index from the array. Downsize the array
if needed. The array capacity will not get lower than the initial
capacity (INIT_CAP). If the index is greater than the array size or if
the index is negative, the function returns OK and the array is
not modified. Returns ERROR is the array cannot be downsized. */
extern int array_remove_byindex(array *a, size_t index);

/* Remove element at address. The address should be the result of the
array_search function. */
extern int array_remove_byaddr(array *a, void *addr);

/* Sort the array in the ascending order based on the comparison function
pointed to by compar, which is called with two arguments that point to the
objects being compared.
Example comparison function for a resizable array of ints:
int array_int_comp(const void *a, const void *b) {
	return ( *(int *)a > *(int *)b);
} */
extern void array_qsort(array *a, int (*compar)(const void *x, const void *y));

/* Return the number of elements currently held into the array.*/
extern int array_size(array *a);

/* Return the maximum number of elements the current array can
hold.*/
extern int array_cap(array *a);

/* When done, free all the memory that the array_init and array_add
might have requested from the system. */
extern void array_destroy(array *a);

#endif // ARRAY_H
