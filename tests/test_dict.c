/* test_dict.c - Tests for the generic dictionary data structure
 */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h> // abs
#include <string.h>
#include "dict.h"

// Use a city member for the dictionary.
typedef struct {
	size_t size; // Size of the city
	char *name;  // Name of the city
} city;

// ***** Helper functions *****
// Comparison function for city objects. It has the same return values as
// the standsrd strcmp function.
static int city_comp_byname(const void *a, const void *b);
// Search city by name and assert the result with the expected size.
static void city_search_byname(dict *d, city *city_with_name, int exp_size);

static void test_dict_search();

void run_all_dict_tests() {
	test_dict_search();
}

static void test_dict_search() {
	// Test a dictionary of city objects.
	dict d;
	dict_init(&d, sizeof(city), city_comp_byname);

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

static int city_comp_byname(const void *a, const void *b) {
	city *citya = (city *)a;
	city *cityb = (city *)b;
	
	return strcmp(citya->name, cityb->name);
}

static void city_search_byname(dict *d, city *city_with_name, int exp_size) {
	city *res = dict_search(d, city_with_name);
	if (res != NULL)
		assert(res->size == exp_size);
	else
		assert(0 && "Dictionary search returned NULL");
}
