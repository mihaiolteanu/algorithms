#include "common_int_member.h"

int comp_int_member(const void *a, const void *b) {
	int avalue = *(int *)a;
	int bvalue = *(int *)b;

	if (avalue < bvalue)
		return -1;
	return avalue > bvalue;
}
