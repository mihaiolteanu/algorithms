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

// initial array capacity
#define INIT_CAP 4

// auto-resizable array structure
typedef struct {
	size_t size;  // number of elements currently in the array
	size_t cap;   // maximum number of elements allowed
	size_t tsize; // size of one data element
	void *data;   // array elements
} array;

/* Initialize the array with sizeof of one of the elements
that it will hold. Returns ERROR if array could not be initialized,
OK otherwise*/
extern int array_init(array *a, size_t elem_size);

/* Add the contents at the specified address, elem_address, to
the array and increases the array size. The number of bytes 
copied depends on the elem_size the array was initialized with.
If the array is full, it doubles it's capacity. If the capacity
cannot be increased, return ERROR. Return OK otherwise.*/
extern int array_add(array *a, void *elem_addr);

/* Return the address of the index position in the array. If
the index is greater than the array size, or if the index is
negative, return NULL. The number of safely accesible bytes
at the return address is equal to the elem_size specified
when array_init was called. */
extern void *array_value(array *a, size_t index);

/* Remove element at index from the array. Downsize the array
if needed. The array capacity will not get lower than the initial
capacity (INIT_CAP). If the index is greater than the array size or if
the index is negative, the function returns OK and the array is
not modified. Returns ERROR is the array cannot be downsized. */
extern int array_remove(array *a, size_t index);

/* Return the number of elements currently held into the array.*/
extern int array_size(array *a);

/* Return the maximum number of elements the current array can
hold.*/
extern int array_cap(array *a);

/* When done, free all the memory that the array_init and array_add
might have requested from the system. */
extern void array_destroy(array *a);

#endif // ARRAY_H
