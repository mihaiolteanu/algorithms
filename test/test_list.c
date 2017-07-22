#include "list.h"
#include "unity.h"
/* #include "common_city_struct.h" */

void test_list_search() {
    list l;
    TEST_ASSERT_EQUAL(1, 1);
}

// ***** Test functions *****
/* static void test_list_search(); */
/* static void test_list_remove(); */

/* void run_all_list_tests() { */
/* 	test_list_search(); */
/* 	test_list_remove(); */
/* } */

/* static void test_list_search() { */
/* 	list l; */
/* 	list_init(&l, sizeof(city), comp_city_byname); */

/* 	// Insert some cities. */
/* 	city_insert(&l, (adt_add_fn_t)list_add, cities_sb_cj_ab); */

/* 	// Now let's find them by name. */
/* 	for (int i = 0; i < CITIES_SB_CJ_AB_SIZE; i++) */
/* 		city_search_byname(&l, (adt_search_fn_t)list_search, */
/* 				   &cities_sb_cj_ab[i], */
/* 				   cities_sb_cj_ab[i].size); */

/* 	list_destroy(&l); */
/* } */

/* static void test_list_remove() { */
/* 	list l; */
/* 	list_init(&l, sizeof(city), comp_city_byname); */

/* 	// Insert some cities. */
/* 	city_insert(&l, (adt_add_fn_t)list_add, cities_sb_cj_ab); */

/* 	//Remove an element from the middle of the list. */
/* 	city *c = &cities_sb_cj_ab[1]; */
/* 	list_remove(&l, c); */

/* 	// It should not be in the list anymore. */
/* 	city *res = list_search(&l, c); */
/* 	assert(res == NULL); */

/* 	// But the others should. */
/* 	c = &cities_sb_cj_ab[0]; */
/* 	city_search_byname(&l, (adt_search_fn_t)list_search, c, c->size); */
/* 	c = &cities_sb_cj_ab[2]; */
/* 	city_search_byname(&l, (adt_search_fn_t)list_search, c, c->size); */

/* 	list_destroy(&l); */
/* } */

