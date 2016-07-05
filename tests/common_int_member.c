#include "common_int_member.h"

int comp_int_member(const void *a, const void *b) {
	int avalue = *(int *)a;
	int bvalue = *(int *)b;

	if (avalue < bvalue)
		return -1;
	return avalue > bvalue;
}

void insert_ints(void *data_type, add_fn_t add_fn, int *ints, int count) {
	for (int i = 0; i < count; i++)
		add_fn(data_type, &ints[i]);
}
