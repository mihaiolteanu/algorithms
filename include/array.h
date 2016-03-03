/* array.h 
   Implementation of a resizable array.
*/

#ifndef ARRAY_H
#define ARRAY_H

// initial array capacity
#define INIT_CAP 4

// auto-resizable array structure
typedef struct {
	int size;   // number of elements currently in the array
	int cap;    // maximum number of elements allowed in the array
	int *head;  // first element of the array
} array;

/* add a new entry to the array; resize array if necessary
used to initialized the array as well. *a should be a null
pointer the first time the function is called. Return OK on success.*/
extern int array_add(array **a, int v);

/* remove an element from the array at the given index.
this is a O(1) operation, as the element to be removed is swapped
with the last element of the array, downsizing at the same time,
if necessary. *a is assigned to NULL if this is the last element
in the array. Return OK on success. Result is stored in res. */
extern int array_remove(array **a, int i, int *res);

/* remove an element from the array at the given index.
this is an O(n) operation, as the elements following the removed
element at index i are shifted to the left to fill the position.
Returns OK on success, ERROR on failure. Result is stored in res. */
extern int array_delete(array **a, int i, int *res);

// get the value stored in the array at index i
extern int array_value(array *a, int i);

// return the number of elements in the array
extern int array_size(array *a);

// return the array capacity
extern int array_cap(array *a);

// pretty-print the array
extern void array_print(array *a);

#endif // ARRAY_H
