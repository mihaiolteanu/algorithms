#include <string.h>
#include <assert.h>
#include "common_city_struct.h"

static int comp_city_byname_fn(const void *a, const void *b) {
	city *citya = (city *)a;
	city *cityb = (city *)b;
	
	return strcmp(citya->name, cityb->name);
}

comp_fn_t comp_city_byname = comp_city_byname_fn;

city cities_sb_cj_ab[CITIES_SB_CJ_AB_SIZE] = {
	{150, "sibiu"},
	{300, "cluj"},
	{200, "alba"},
};

void city_insert(void *adt,
		 int (*adt_add)(void *adt, void *elem_addr),
		 city *cities) {
	city *c;
	for (int i = 0; i < CITIES_SB_CJ_AB_SIZE; i++)
		adt_add(adt, &cities[i]);
}
		
void city_search_byname(void *adt,
		 int (*adt_search)(void *adt, void *elem_addr),
		 city *c, int exp_size) {
	city *res = adt_search(adt, c);
	if (res != NULL)
		assert(res->size == exp_size);
	else
		assert(0 && "City search returned NULL");
}
