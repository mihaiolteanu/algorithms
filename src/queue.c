#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "system.h"

int queue_init(queue *q, size_t tsize) {
	array *a;

	a = q->a = malloc(sizeof(array));
	if (a == NULL)
		return ERROR;
	return array_init(a, tsize);
}

int queue_enqueue(queue *q, void *x) {
	array *a = q->a;

	return array_add(a, x);	
}

void *queue_dequeue(queue *q) {
	array *a = q->a;
	size_t size = array_size(a);

	if (size < 1)
		return NULL; // Empty queue
	void *data_addr = array_value(a, 0);

	// Copy the contents of the data_addr, otherwise removing the
	// element from the array might override it.
	void *data = malloc(sizeof(a->tsize));
	memcpy(data, data_addr, a->tsize);		
	
	array_remove(a, 0);
	// Don't forget to free the data after you use it.
	return data;
}

void queue_destroy(queue *q) {
	array *a = q->a;

	free(a);
}
