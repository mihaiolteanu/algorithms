/* test_list.c - Tests for the generic linked list data structure 
 */

#include <string.h>
#include <assert.h>
#include "list.h"
#include "system.h"
#include "common_city_struct.h"

// ***** Test functions *****
static void test_list_search();
static void test_list_remove();

// ***** Helper functions *****
// Search city by name and assert the result with the expected size.
static void city_search_byname(list *l, city *city_with_name, int exp_size);

void run_all_list_tests() {
	test_list_search();
	test_list_remove();
}

static void test_list_search() {
	list l;
	list_init(&l, sizeof(city), comp_city_byname);

	// Insert some cities.
	// TODO: same as dict tests. Should be made into a seperate function,
	// eventually with vargs.
	city sb = {150, "sibiu"};
	city cj = {300, "cluj"};
	city ab = {200, "alba"};
	list_add(&l, &cj);
	list_add(&l, &ab);
	list_add(&l, &sb);

	// Now let's find them by name.
	city tosearch = {0, "sibiu"};
	city_search_byname(&l, &tosearch, 150);
	tosearch.name = "cluj";
	city_search_byname(&l, &tosearch, 300);
	tosearch.name = "alba";
	city_search_byname(&l, &tosearch, 200);

	list_destroy(&l);
}

static void test_list_remove() {
	list l;
	list_init(&l, sizeof(city), comp_city_byname);

	// Insert some cities.
	// TODO: same as dict tests. Should be made into a seperate function,
	// eventually with vargs.
	city sb = {150, "sibiu"};
	city cj = {300, "cluj"};
	city ab = {200, "alba"};
	list_add(&l, &cj);
	list_add(&l, &ab);
	list_add(&l, &sb);

	city toremove = {0, "alba"};
	//Remove an element from the middle of the list.
	list_remove(&l, &toremove);

	// It should not be in the list anymore.
	city tosearch = {0, "alba"};
	city *res = list_search(&l, &tosearch);
	assert(res == NULL);

	// But the others should.
	tosearch.name = "cluj";
	city_search_byname(&l, &tosearch, 300);
	tosearch.name = "sibiu";
	city_search_byname(&l, &tosearch, 150);

	list_destroy(&l);
}

static void city_search_byname(list *l, city *city_with_name, int exp_size) {
	city *res = list_search(l, city_with_name);
	if (res != NULL)
		assert(res->size == exp_size);
	else
		assert(0 && "Dictionary search returned NULL");
}

