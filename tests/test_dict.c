/* test_dict.c - Tests for the generic dictionary data structure
 */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h> // abs
#include <string.h>
#include "dict.h"
#include "common_city_struct.h"

// ***** Helper functions *****
// Search city by name and assert the result with the expected size.
static void city_search_byname(dict *d, city *city_with_name, int exp_size);

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
	city sb = {150, "sibiu"};
	city cj = {300, "cluj"};
	city ab = {200, "alba"};
	dict_insert(&d, &cj); // First element
	dict_insert(&d, &ab); // Add at the beginning
	dict_insert(&d, &sb); // Add at the end

	// Now let's find them by name.
	city tosearch = {0, "sibiu"};
	city_search_byname(&d, &tosearch, 150);

	tosearch.name = "cluj";
	city_search_byname(&d, &tosearch, 300);

	tosearch.name = "alba";
	city_search_byname(&d, &tosearch, 200);

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
	city sb = {150, "sibiu"};
	city cj = {300, "cluj"};
	city ab = {200, "alba"};
	dict_insert(&d, &cj); // First element
	dict_insert(&d, &ab); // Add at the beginning
	dict_insert(&d, &sb); // Add at the end

	// alba should be first.
	res = dict_min(&d);
	assert(strcmp(res->name, "alba") == 0);

	// sibiu should be last.
	res = dict_max(&d);
	assert(strcmp(res->name, "sibiu") == 0);

}

static void city_search_byname(dict *d, city *city_with_name, int exp_size) {
	city *res = dict_search(d, city_with_name);
	if (res != NULL)
		assert(res->size == exp_size);
	else
		assert(0 && "Dictionary search returned NULL");
}
