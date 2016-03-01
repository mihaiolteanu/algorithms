#include "stack.h"
#include "array.h"
#include "system.h"

int push(stack **s, int x) {
	stack *sp = *s;
	
	return array_add(&sp->array, x);
}

int pop(stack **s) {
	
}
