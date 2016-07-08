#include <stdlib.h>
#include "dict.h"
#include "sarray.h"
#include "system.h"

static void *dict_init_sarray(dict_sarray *d, size_t elem_size, comp_fn_t comp);
static void *dict_init_list(dict_list *d, size_t elem_size, comp_fn_t comp);

typedef void *(*dict_init_fn_t)(void *d, size_t elem_size, comp_fn_t comp);
typedef void *(*dict_search_fn_t)(void *d, void *elem_addr);
typedef void *(*dict_insert_fn_t)(void *d, void *elem_addr);
typedef void *(*dict_max_fn_t)(void *d);
typedef void *(*dict_min_fn_t)(void *d);
typedef void *(*dict_destroy_fn_t)(void *d);

static dict_init_fn_t dict_init_fns[DICT_TYPE_LAST] = {
	(dict_init_fn_t)dict_init_sarray,
	(dict_init_fn_t)dict_init_list
};


int dict_init(void *d, size_t elem_size, comp_fn_t comp, dict_dtype dtype) {
	return dict_init_fns[dtype](d, elem_size, comp);
}

void *dict_search(void *d, void *elem_addr) {
	sarray *as = &((dict_sarray*)d)->as;;
	
	return sarray_search(as, elem_addr);
}

int dict_insert(void *d, void *elem_addr) {
	sarray *as = &((dict_sarray*)d)->as;;

	return sarray_add(as, elem_addr);
}

void dict_remove(void *d, void *x) {
	sarray *as = &((dict_sarray*)d)->as;;

	sarray_remove_byaddr(as, x);
}

void *dict_max(void *d) {
	sarray *as = &((dict_sarray*)d)->as;;
	int size = sarray_size(as);

	return sarray_value(as, size - 1);
}

void *dict_min(void *d) {
	sarray *as = &((dict_sarray*)d)->as;;
	int size = sarray_size(as);

	if (size > 0)
		return sarray_value(as, 0);
	return NULL;
}

int *dict_destroy(void *d) {
	sarray *as = &((dict_sarray*)d)->as;;

	sarray_destroy(as);
	free(as);
}

static void *dict_init_sarray(dict_sarray *d, size_t elem_size, comp_fn_t comp) {
	sarray *as = &d->as;
	return (void *)sarray_init(as, elem_size, comp);
}
	
static void *dict_init_list(dict_list *d, size_t elem_size, comp_fn_t comp) {
	list *l = &d->l;
	list_init(l, elem_size, comp);
	return (void *)1;
}
