#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "array.h"
#include "system.h"

int stack_push(stack **s, int x) {
	stack *sp;

	if (*s == NULL) {
		sp = *s = malloc(sizeof(stack));
		if (sp == NULL)
			return ERROR;
		(*s)->a = NULL;
	}
	sp = *s;
	
	return array_add(&sp->a, x);
}

int stack_pop(stack **s) {
	stack *sp = *s;
	int res;
	
	array_remove(&sp->a, sp->a->size - 1, &res);
	return res;
}

int stack_size(stack *s) {
	// poping the last element from the stack will
	// leave the array pointer as NULL
	if (s->a == NULL)
		return 0;
	return s->a->size;
}
