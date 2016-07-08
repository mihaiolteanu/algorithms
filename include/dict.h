/* dict.h - Interface for a generic dictionary implemented with different data
 * structures. The user must define what data underlining data structure to use
 * before including this header in his source code. If the header is included
 * without a define, the default data structure will be used.
 */

#ifndef DICT_H
#define DICT_H

#include <stddef.h>
#include "list.h"
#include "sarray.h"
#include "bst.h"
#include "bbst.h"
#include "system.h"


typedef enum {
//	DICT_DEFAULT,
	DICT_SARRAY = 0,
	DICT_LIST,
	DICT_BST,
	DICT_BBST,
	DICT_HASH,
	DICT_TYPE_LAST
} dict_dtype;

/* The dictionary data structure contains different elements based on the
 * underlining data structure used to implement it. */
typedef struct {
	sarray as;
} dict_sarray;

typedef struct {
	list l;
} dict_list;

typedef struct {
	bst b;
} dict_bst;

typedef struct {
	bbst b;
} dict_bbst;

typedef struct {
	/* Not implemented yet. */
} dict_hash;

typedef struct {
	void *dt;
	dict_dtype dtype;
} dict;

/* Initialize a new dictionary. The comparison function decides when two
 * elements of the same type are equal. dtype is the underlining data structure
 * used to implement the dictionary.  */
extern int dict_init(dict *d, size_t elem_size, comp_fn_t comp,
		     dict_dtype dtype);

/* Given a pointer to an element of the type the dictionary holds, return a
 * pointer to the element in the dictionary whose key matches the key of the
 * given element, if one exists. The key of the element is defined by
 * the comparison function. The function signature differs from the one given in
 * the book (pg. 72), but if I use the element and not it's key I don't have to
 * have two comparison functions, one for the element and one for the element's
 * key. */
extern void *dict_search(dict *d, void *elem_addr);

/* Given a pointer to an element of the type the dictionary holds, insert the
 * element in the dictionary. */
extern int dict_insert(dict *d, void *elem_addr);

/* Given a pointer to an element already in the dictionary, remove it from the
 * dictionary. */
extern void dict_delete(dict *d, void *dict_elem_addr);

/* Retrieve the item with the largest (or smallest) key from the dictionary. */
extern void *dict_max(dict *d);
extern void *dict_min(dict *d);

/* Retrieve the item from the dictionary whose key is immediately before (or
 * after) the element in sorted order. The key is defined by the comp function*/
extern void *dict_predecessor(dict *d, void *elem_addr);
extern void *dict_successor(dict *d, void *elem_addr);

/* Cleanup the dictionary when it's no longer needed. */
extern int *dict_destroy(dict *d);

#endif // DICT_H
