#include "queue.h"
#include "unity.h"

void test_queue_enqueue_dequeue() {
	// Test a queue of ints.
	queue q;
	queue_init(&q, sizeof(int));
	size_t elems = 5;

	// Enqueue some elements.
	for (int i = 0; i < elems; i++)
		queue_enqueue(&q, &i);

	// Dequeue and check the correct order.
	for (int i = 0; i < elems; i++) {
		int top = *(int*)queue_dequeue(&q);
		TEST_ASSERT_EQUAL_INT(top, i);
	}
}


