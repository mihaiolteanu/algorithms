#include <stdio.h>
#include <assert.h>
#include "array.h"

int main(void) {
	array *a = NULL;

	for(int i = 0; i < 1; i++)
		assert(array_add(&a, i)); 
	array_delete(&a, 0);

	assert(a == NULL);
	array_print(a);

	return 0;
}
