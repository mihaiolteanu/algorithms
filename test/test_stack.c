#include "stack.h"
#include "unity.h"

void test_stack_push_pop() {
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
		TEST_ASSERT_EQUAL(top, elems - 1 - i);
	}

	// Pop from an empty stack should have no side-effects.
	stack_pop(&s);
	stack_destroy(&s);
}
