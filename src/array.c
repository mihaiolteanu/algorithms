#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "system.h"

// downsize and free the array, if needed.
// to be called from delete/remove/free/etc operations
static void down_and_free(array **a);

int array_add(array **a, int v) {
	array *ap;

	if (*a == NULL) {          // initialization
		ap = *a = malloc(sizeof(array));
		if (ap == NULL)
			return ERROR;
		ap->head = malloc(INIT_CAP*sizeof(int));
		if (ap->head == NULL)
			return ERROR;
		ap->size = 0;
		ap->cap = INIT_CAP;
	} else
		ap = *a;
	
	if (ap->size == ap->cap) { // array is full, so double its capacity
		int *tmp_head = realloc(ap->head, 2*ap->cap*sizeof(int));
		if (tmp_head == NULL)
			return ERROR;
		ap->head = tmp_head;
		ap->cap = 2*ap->cap;
	}
	ap->head[ap->size++] = v;
	return OK;
}

static void down_and_free(array **a) {
	array *ap = *a;

	// downsize the array if needed
	if (ap->size < ap->cap / 2) {
		*a = realloc(*a, ap->cap / 2);
		ap->cap = ap->cap / 2;
	}

	// free the space occupied by the array if needed
	if (ap->size == 0) {
		free(ap->head);
		free(ap);
		*a = NULL;
	}
}

int array_remove(array **a, int i) {
	array *ap;
	int *head;
	
	if (*a == NULL)
		return ERROR;

	ap = *a;
	head = ap->head;

	if (ap->size <= i)
		return ERROR;
	// switch the element to be removed with the last element
	// of the array
	head[i] = head[ap->size - 1];
	ap->size--;

	down_and_free(a);
	return OK;
}

int array_delete(array **a, int i) {
	array *ap;
	int *head;

	if (*a == NULL)
		return ERROR;

	ap = *a;
	head = ap->head;

	if (ap->size <= i)
		return ERROR;

	for (int j = i; j < ap->size - 1; j++)
		head[j] = head[j+1];
	ap->size--;

	down_and_free(a);
	return OK;
}

int array_value(array *a, int i) {
	return (a->head)[i];
}

int array_size(array *a) {
	return a->size;
}

int array_cap(array *a) {
	return a->cap;
}

void array_print(array *a) {
	if (a == NULL)
		return;
	for(int i = 0; i < a->size; i++)
		printf("%d ", a->head[i]);
	printf("\n");
}
