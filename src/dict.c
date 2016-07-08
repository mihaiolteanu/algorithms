#include <stdlib.h>
#include "dict.h"
#include "sarray.h"
#include "system.h"

static void *dict_init_sarray(dict *d, size_t elem_size, comp_fn_t comp,
			      dict_dtype dtype);
static void *dict_init_list(dict *d, size_t elem_size, comp_fn_t comp,
			    dict_dtype dtype);

static void *dict_search_sarray(dict *d, void *elem_addr);
static void *dict_search_list(dict *d, void *elem_addr);

static void *dict_insert_sarray(dict *d, void *elem_addr);
static void *dict_insert_list(dict *d, void *elem_addr);

static void dict_destroy_sarray(dict *d);
static void dict_destroy_list(dict *d);

typedef void *(*dict_init_fn_t)(dict *d, size_t elem_size, comp_fn_t comp,
				dict_dtype dtype);
typedef void *(*dict_search_fn_t)(dict *d, void *elem_addr);
typedef void *(*dict_insert_fn_t)(dict *d, void *elem_addr);
typedef void *(*dict_max_fn_t)(dict *d);
typedef void *(*dict_min_fn_t)(dict *d);
typedef void (*dict_destroy_fn_t)(dict *d);

static dict_init_fn_t dict_init_fns[DICT_TYPE_LAST] = {
	dict_init_sarray,
	dict_init_list
};

static dict_search_fn_t dict_search_fns[DICT_TYPE_LAST] = {
	dict_search_sarray,
	dict_search_list
};

static dict_insert_fn_t dict_insert_fns[DICT_TYPE_LAST] = {
	dict_insert_sarray,
	dict_insert_list
};

static dict_destroy_fn_t dict_destroy_fns[DICT_TYPE_LAST] = {
	dict_destroy_sarray,
	dict_destroy_list
};

int dict_init(dict *d, size_t elem_size, comp_fn_t comp, dict_dtype dtype) {
	return dict_init_fns[dtype](d, elem_size, comp, dtype);
}

void *dict_search(dict *d, void *elem_addr) {
	dict_dtype dtype = d->dtype;
	return dict_search_fns[dtype](d, elem_addr);
}

int dict_insert(dict *d, void *elem_addr) {
	dict_dtype dtype = d->dtype;
	return dict_insert_fns[dtype](d, elem_addr);
}

void dict_remove(dict *d, void *x) {
	sarray *as = d->dt;;

	sarray_remove_byaddr(as, x);
}

void *dict_max(dict *d) {
	sarray *as = d->dt;;
	int size = sarray_size(as);

	return sarray_value(as, size - 1);
}

void *dict_min(dict *d) {
	sarray *as = d->dt;;
	int size = sarray_size(as);

	if (size > 0)
		return sarray_value(as, 0);
	return NULL;
}

int *dict_destroy(dict *d) {
	dict_dtype dtype = d->dtype;
	dict_destroy_fns[dtype](d);
}

static void *dict_init_sarray(dict *d, size_t elem_size, comp_fn_t comp,
			      dict_dtype dtype) {
	sarray *sa;

	if ((sa = malloc(sizeof(sarray))) == NULL)
		return NULL;
	d->dt = sa;
	d->dtype = dtype;
	return (void *)sarray_init(sa, elem_size, comp);
}
	
static void *dict_init_list(dict *d, size_t elem_size, comp_fn_t comp,
			    dict_dtype dtype) {
	list *l;

	if ((l = malloc(sizeof(list))) == NULL)
		return NULL;
	d->dt = l;
	d->dtype = dtype;
	list_init(l, elem_size, comp);
	return (void *)1;
}


static void *dict_search_sarray(dict *d, void *elem_addr) {
	sarray *sa = d->dt;
	return sarray_search(sa, elem_addr);
}

static void *dict_search_list(dict *d, void *elem_addr) {
	list *l = d->dt;
	return list_search(l, elem_addr);
}


static void *dict_insert_sarray(dict *d, void *elem_addr) {
	sarray *as = d->dt;
	return sarray_add(as, elem_addr);
}

static void *dict_insert_list(dict *d, void *elem_addr) {
	list *l = d->dt;
	return list_add(l, elem_addr);
}


static void dict_destroy_sarray(dict *d) {
	sarray *sa = d->dt;
	// sarray_destroy(sa);
	free(sa);
}

static void dict_destroy_list(dict *d) {
	list *l = d->dt;
	// list_destroy(l)
	free(l);
}
