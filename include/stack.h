/* stack.h - implementation of a stack data structure */

#ifndef STACK_H
#define STACK_H

#include "array.h"

typedef struct {
	array *a;
} stack;

// insert item x at the top of the stack s
// at first call, *s must be null
extern int stack_push(stack **s, int x);

// return and remove the top item of the stack s
// *s will be set to null if stack is empty
extern int stack_pop(stack **s);

extern int stack_size(stack *s);

#endif // STACK_H
