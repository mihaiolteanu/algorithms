#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "array.h"
#include "system.h"

int stack_init(stack *s, size_t tsize) {
	array *a;
	a = s->a = malloc(sizeof(array));
	if (a == NULL)
		return ERROR;

	return array_init(a, tsize);
}

int stack_push(stack *s, void *x) {
	array *a = s->a;
	return array_add(a, x);
}

void *stack_pop(stack *s) {
	array *a = s->a;
	size_t size = array_size(a);
	void *ret = array_value(a, size - 1);

	array_remove_byindex(a, size - 1);

	return ret;
}

size_t stack_size(stack *s) {
	array *a = s->a;
	size_t size = a->size;

	return size;
}

extern void stack_destroy(stack *s) {
	array *a = s->a;
	
	array_destroy(a);
	free(a);
}
	
