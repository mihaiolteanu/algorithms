/* test_dict.c - Tests for the generic dictionary data structure
 */

#include <assert.h>
#include "dict.h"
#include "common_city_struct.h"

static void test_dict_search();
static void test_dict_max_min();

void run_all_dict_tests() {
	test_dict_search();
	test_dict_max_min();
}

static void test_dict_search() {
	// Test a dictionary of city objects.
	dict d;
	dict_init(&d, sizeof(city), comp_city_byname);

	// Insert some cities.
	city_insert(&d, dict_insert, cities_sb_cj_ab);

	for (int i = 0; i < CITIES_SB_CJ_AB_SIZE; i++)
		city_search_byname(&d, dict_search,
				   &cities_sb_cj_ab[i],
				   cities_sb_cj_ab[i].size);

	dict_destroy(&d);
}

static void test_dict_max_min() {
	// Test a dictionary of city objects.
	dict d;
	city *res;
	dict_init(&d, sizeof(city), comp_city_byname);

	// Nothing added yet, so no min nor max exists.
	res = dict_min(&d);
	assert(res == NULL);
	res = dict_max(&d);
	assert(res == NULL);	

	// Insert some cities.
	city_insert(&d, dict_insert, cities_sb_cj_ab);

	// alba should be first.
	res = dict_min(&d);
	assert(strcmp(res->name, "alba") == 0);

	// sibiu should be last.
	res = dict_max(&d);
	assert(strcmp(res->name, "sibiu") == 0);
}
