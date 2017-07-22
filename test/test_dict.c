#include "dict.h"
#include "common_int_member.h"
#include "system.h"
#include "unity.h"

void test_dict_search() {
	dict d;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);

	for (dict_dtype dtype = DICT_SARRAY; dtype < DICT_HASH; dtype++) {
		dict_init(&d, sizeof(int), comp_int_member, dtype);
		insert_ints(&d, (add_fn_t)dict_insert, ints, ints_size);
		assert_ints(&d, (search_fn_t)dict_search, ints, ints_size);
		dict_destroy(&d);
	}
}

void test_dict_max_min() {
	dict d;
	int ints[] = {2, 5, 3, 10, 1};
	int ints_size = ARRAY_SIZE(ints);
	int *min, *max;

	for (dict_dtype dtype = DICT_SARRAY; dtype < DICT_HASH; dtype++) {
		dict_init(&d, sizeof(int), comp_int_member, dtype);
		insert_ints(&d, (add_fn_t)dict_insert, ints, ints_size);
		min = dict_min(&d);
		max = dict_max(&d);
		TEST_ASSERT_EQUAL_INT(*min, 1);
		TEST_ASSERT_EQUAL_INT(*max, 10);
		dict_destroy(&d);
	}
}

