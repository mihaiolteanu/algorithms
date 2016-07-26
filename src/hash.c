#include "hash.h"
#include "list.h"

extern void *hash_init(hash_table *h, size_t elem_size,
		       hash_fn_t hash_fn, comp_fn_t comp,
		       unsigned long table_size) {
	array *a;
	if ((a = malloc(sizeof(array))) == NULL)
		return NULL;
	h->a = a;
	h->table_size = table_size;
	h->tsize = elem_size;
	h->hash_fn = hash_fn;
	h->comp = comp;
	array_init(a, sizeof(list*), NULL);
	/* Initialize the hash table with NULL pointers */
	list *init_val = NULL;
	array_expand_fill(a, table_size, &init_val);
	return NULL;
}

void *hash_search(hash_table *h, void *elem_addr) {
	array *a = h->a;
	size_t size = a->size;
	hash_fn_t hash_fn = h->hash_fn;
	unsigned long hash_res = hash_fn(elem_addr);
	unsigned long index = hash_res % h->table_size;
	list *l;

	if (index >= size)
		return NULL; /* Not found. */
	/* The array_value returns a pointer to my stored data, and what I'm
	   storing is a pointer (to a list). This is the reason for casting. */
	l = *(list**)array_value(a, index);
	return list_search(l, elem_addr);
}

void *hash_insert(hash_table *h, void *elem_addr) {
	array *a = h->a;
	hash_fn_t hash_fn = h->hash_fn;
	unsigned long hash_res = hash_fn(elem_addr);
	unsigned long index = hash_res % h->table_size;
	list *l;

	/* Resolve collision if needed, create new list otherwise. */
	l = *(list**)array_value(a, index);
	if (l == NULL) { /* No collision - create new slot. */
		if ((l = malloc(sizeof(list))) == NULL)
			return NULL;
		list_init(l, h->tsize, h->comp);
		/* The array stores a pointer to my data, and what I'm storing
		   is a pointer (to a list). This is the reason for passing the
		   list pointer address and not the list pointer itself. */
		array_add_at_index(a, &l, index);
	}
	list_add(l, elem_addr);

	return elem_addr;
}

void hash_destroy(hash_table *h) {
	array *a = h->a;
	unsigned long table_size = h->table_size;
	list *l;

	for (int i = 0; i < table_size; i++) {
		l = *(list**)array_value(a, i);
		if (l != NULL) {
			list_destroy(l);
			free (l);
		}
	}
	free(a);
}
