#include <string.h>
#include <assert.h>
#include "common_city_struct.h"

static int comp_city_byname_fn(const void *a, const void *b) {
	city *citya = (city *)a;
	city *cityb = (city *)b;
	
	return strcmp(citya->name, cityb->name);
}

comp_fn_t comp_city_byname = comp_city_byname_fn;
