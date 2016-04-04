#include <assert.h>
#include <stddef.h>
#include "stack.h"

static void test_stack_push_pop();

void run_all_stack_tests() {
	test_stack_push_pop();
}

static void test_stack_push_pop() {
	// Test a stack of ints.
	stack s;
	stack_init(&s, sizeof(int));
	size_t elems = 5;

	// Push some elements into the stack.
	for (int i = 0; i < elems; i++)
		stack_push(&s, &i);

	// Pop the elements and check the correct order.
	for (int i = 0; i < elems; i++) {
		int top = *(int*)stack_pop(&s);
		assert(top == elems - 1 - i);
	}

	// Pop from an empty stack should have no side-effects.
	stack_pop(&s);

	stack_destroy(&s);
}
