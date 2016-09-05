#include <stdlib.h>
#include "dict.h"
#include "sarray.h"
#include "list.h"
#include "bst.h"
#include "system.h"

/* Dictionary sorted array declarations. */
static void *dict_init_sarray(dict *d, size_t elem_size, comp_fn_t comp);
static void *dict_search_sarray(dict *d, void *elem_addr);
static void *dict_insert_sarray(dict *d, void *elem_addr);
static void *dict_max_sarray(dict *d);
static void *dict_min_sarray(dict *d);
static void *dict_predecessor_sarray(dict *d, void *elem_addr);
static void *dict_successor_sarray(dict *d, void *elem_addr);
static void dict_destroy_sarray(dict *d);

/* Dictionary linked list declarations. */
static void *dict_init_list(dict *d, size_t elem_size, comp_fn_t comp);
static void *dict_search_list(dict *d, void *elem_addr);
static void *dict_insert_list(dict *d, void *elem_addr);
static void *dict_max_list(dict *d);
static void *dict_min_list(dict *d);
static void *dict_predecessor_list(dict *d, void *elem_addr);
static void *dict_successor_list(dict *d, void *elem_addr);
static void dict_destroy_list(dict *d);

/* Dictionary binary search tree declarations. */
static void *dict_init_bst(dict *d, size_t elem_size, comp_fn_t comp);
static void *dict_search_bst(dict *d, void *elem_addr);
static void *dict_insert_bst(dict *d, void *elem_addr);
static void *dict_max_bst(dict *d);
static void *dict_min_bst(dict *d);
static void *dict_predecessor_bst(dict *d, void *elem_addr);
static void *dict_successor_bst(dict *d, void *elem_addr);
static void dict_destroy_bst(dict *d);

/* Dictionary balanced binary search tree declarations. */
static void *dict_init_bbst(dict *d, size_t elem_size, comp_fn_t comp);
static void *dict_search_bbst(dict *d, void *elem_addr);
static void *dict_insert_bbst(dict *d, void *elem_addr);
static void *dict_max_bbst(dict *d);
static void *dict_min_bbst(dict *d);
static void *dict_predecessor_bbst(dict *d, void *elem_addr);
static void *dict_successor_bbst(dict *d, void *elem_addr);
static void dict_destroy_bbst(dict *d);

/* Dictionary hash table declarations. */
static void *dict_init_hash(dict *d, size_t elem_size, comp_fn_t comp);
static void *dict_search_hash(dict *d, void *elem_addr);
static void *dict_insert_hash(dict *d, void *elem_addr);
static void *dict_max_hash(dict *d);
static void *dict_min_hash(dict *d);
static void *dict_predecessor_hash(dict *d, void *elem_addr);
static void *dict_successor_hash(dict *d, void *elem_addr);
static void dict_destroy_hash(dict *d);

/* Typedefs */
typedef void *(*dict_init_fn_t)(dict *d, size_t elem_size, comp_fn_t comp);
typedef void *(*dict_search_fn_t)(dict *d, void *elem_addr);
typedef void *(*dict_insert_fn_t)(dict *d, void *elem_addr);
typedef void *(*dict_max_fn_t)(dict *d);
typedef void *(*dict_min_fn_t)(dict *d);
typedef void (*dict_destroy_fn_t)(dict *d);

typedef struct {
	dict_init_fn_t dict_init_fn;
	dict_search_fn_t dict_search_fn;
	dict_insert_fn_t dict_insert_fn;
	dict_max_fn_t dict_max_fn;
	dict_min_fn_t dict_min_fn;
	dict_destroy_fn_t dict_destroy_fn;
} dict_fns_t;

/* All the dictionary functions in a single, easy accessible place. */
static dict_fns_t dict_fns[DICT_TYPE_LAST] = {
	{ dict_init_sarray, dict_search_sarray, dict_insert_sarray, /* sarray */
	  dict_max_sarray, dict_min_sarray, dict_destroy_sarray },
	{ dict_init_list, dict_search_list, dict_insert_list,       /* list */ 
	  dict_max_list, dict_min_list, dict_destroy_list },
	{ dict_init_bst, dict_search_bst, dict_insert_bst,          /* bst */
	  dict_max_bst, dict_min_bst, dict_destroy_bst},
	{ dict_init_bbst, dict_search_bbst, dict_insert_bbst,       /* bbst */
	  dict_max_bbst, dict_min_bbst, dict_destroy_bbst},

};

/* Public interfaces. */
void *dict_init(dict *d, size_t elem_size, comp_fn_t comp, dict_dtype dtype) {
	return dict_fns[dtype].dict_init_fn(d, elem_size, comp);
}

void *dict_search(dict *d, void *elem_addr) {
	dict_dtype dtype = d->dtype;
	return dict_fns[dtype].dict_search_fn(d, elem_addr);
}

void *dict_insert(dict *d, void *elem_addr) {
	dict_dtype dtype = d->dtype;
	return dict_fns[dtype].dict_insert_fn(d, elem_addr);
}

void *dict_max(dict *d) {
	dict_dtype dtype = d->dtype;
	return dict_fns[dtype].dict_max_fn(d);
}

void *dict_min(dict *d) {
	dict_dtype dtype = d->dtype;
	return dict_fns[dtype].dict_min_fn(d);
}

int *dict_destroy(dict *d) {
	dict_dtype dtype = d->dtype;
	dict_fns[dtype].dict_destroy_fn(d);
}

/* Dictionary sorted array implementation. */
static void *dict_init_sarray(dict *d, size_t elem_size, comp_fn_t comp) {
	sarray *sa;

	if ((sa = malloc(sizeof(sarray))) == NULL)
		return NULL;
	d->dt = sa;
	d->dtype = DICT_SARRAY;
	d->comp = comp;
	return (void *)sarray_init(sa, elem_size, comp);
}

static void *dict_search_sarray(dict *d, void *elem_addr) {
	sarray *sa = d->dt;
	return sarray_search(sa, elem_addr);
}

static void *dict_insert_sarray(dict *d, void *elem_addr) {
	sarray *as = d->dt;
	return sarray_add(as, elem_addr);
}

static void *dict_max_sarray(dict *d) {
	sarray *sa = d->dt;
	int sa_size = sarray_size(sa);
	if (sa_size > 0)
		return sarray_value(sa, sa_size-1);
	return NULL;
}

static void *dict_min_sarray(dict *d) {
	sarray *sa = d->dt;
	int sa_size = sarray_size(sa);
	if (sa_size > 0)
		return sarray_value(sa, 0);
	return NULL;
}

static void *dict_predecessor_sarray(dict *d, void *elem_addr) {

}

static void *dict_successor_sarray(dict *d, void *elem_addr) {

}

static void dict_destroy_sarray(dict *d) {
	sarray *sa = d->dt;
	// sarray_destroy(sa);
	free(sa);
}


/* Dictionary linked list implementation. */
static void *dict_init_list(dict *d, size_t elem_size, comp_fn_t comp) {
	list *l;

	if ((l = malloc(sizeof(list))) == NULL)
		return NULL;
	d->dt = l;
	d->dtype = DICT_LIST;
	d->comp = comp;
	list_init(l, elem_size, comp);
	return (void *)1;
}

static void *dict_search_list(dict *d, void *elem_addr) {
	list *l = d->dt;
	return list_search(l, elem_addr);
}

static void *dict_insert_list(dict *d, void *elem_addr) {
	list *l = d->dt;
	return list_add(l, elem_addr);
}

static void *dict_max_list(dict *d) {
	comp_fn_t comp = d->comp;
	list *l = d->dt;
	list_node *node = list_first_node(l);
	void *node_data;
	void *max = list_node_data(node);

	while((node = list_next_node(node)) != NULL) {
		node_data = list_node_data(node);
		if (comp(node_data, max) > 0)
			max = node_data;
	}
	return max;
}

static void *dict_min_list(dict *d) {
	comp_fn_t comp = d->comp;
	list *l = d->dt;
	list_node *node = list_first_node(l);
	void *node_data;
	void *min = list_node_data(node);

	while((node = list_next_node(node)) != NULL) {
		node_data = list_node_data(node);
		if (comp(node_data, min) < 0)
			min = node_data;
	}
	return min;
}

static void *dict_predecessor_list(dict *d, void *elem_addr) {

}

static void *dict_successor_list(dict *d, void *elem_addr) {

}

static void dict_destroy_list(dict *d) {
	list *l = d->dt;
	list_destroy(l);
	free(l);
}


/* Dictionary binary search tree implementation. */
static void *dict_init_bst(dict *d, size_t elem_size, comp_fn_t comp) {
	bst *b;

	if ((b = malloc(sizeof(bst))) == NULL)
		return NULL;
	d->dt = b;
	d->dtype = DICT_BST;
	d->comp = comp;
	bst_init(b, elem_size, comp);
	return (void *)1;
}

static void *dict_search_bst(dict *d, void *elem_addr) {
	bst *b = d->dt;
	return bst_search(b, elem_addr);
}

static void *dict_insert_bst(dict *d, void *elem_addr) {
	bst *b = d->dt;
	return bst_insert(b, elem_addr);
}

static void *dict_max_bst(dict *d) {
	bst *b = d->dt;
	return bst_max(b);
}

static void *dict_min_bst(dict *d) {
	bst *b = d->dt;
	return bst_min(b);
}

static void *dict_predecessor_bst(dict *d, void *elem_addr) {

}

static void *dict_successor_bst(dict *d, void *elem_addr) {

}

static void dict_destroy_bst(dict *d) {
	bst *b = d->dt;
	bst_destroy(b);
}


/* Dictionary balanced binary search tree implementation. */
static void *dict_init_bbst(dict *d, size_t elem_size, comp_fn_t comp) {
	bbst *bb;

	if ((bb = malloc(sizeof(bbst))) == NULL)
		return NULL;
	d->dt = bb;
	d->dtype = DICT_BBST;
	d->comp = comp;
	bbst_init(bb, elem_size, comp);
	return (void *)1;
}

static void *dict_search_bbst(dict *d, void *elem_addr) {
	bbst *bb = d->dt;
	return bbst_search(bb, elem_addr);
}

static void *dict_insert_bbst(dict *d, void *elem_addr) {
	bbst *bb = d->dt;
	bbst_insert(bb, elem_addr);
	return NULL;
}

static void *dict_max_bbst(dict *d) {
	bbst *bb = d->dt;
	bst *b = &bb->b;
	return bst_max(b);
}

static void *dict_min_bbst(dict *d) {
	bbst *bb = d->dt;
	bst *b = &bb->b;
	return bst_min(b);
}

static void *dict_predecessor_bbst(dict *d, void *elem_addr) {

}

static void *dict_successor_bbst(dict *d, void *elem_addr) {

}

static void dict_destroy_bbst(dict *d) {
	bbst *bb = d->dt;
	bst *b = &bb->b;
	bst_destroy(b);
	free(bb);
}
