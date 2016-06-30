/* dict.h - Interface for a generic dictionary implemented with different data
 * structures. The user must define what data underlining data structure to use
 * before including this header in his source code. If the header is included
 * without a define, the default data structure will be used.

 * DICT_LIST
 * DICT_SLIST
 *
 */

#ifndef DICT_H
#define DICT_H

#include <stddef.h>
#include "list.h"
#include "sarray.h"
#include "bst.h"
#include "bbst.h"
#include "system.h"

/* The dictionary data structure contains different elements based on the
 * underlining data structure used to implement it. */
typedef struct {
#ifdef DICT_LIST
#define DSTRUCT list
	list l;
#elif DICT_SLIST
#define DSTRUCT slist
	slist sl;
#elif DICT_BST
#define DSTRUCT bst
	bst b;
#elif DICT_BBST
#define DSTRUCT bbst
	bbst bb;
#elif DICT_HASH
#define DSTRUCT hash
	hash h;
#else
#define DSTRUCT sarray
	sarray as;
#endif
} dict;

/* Initialize a new dictionary. The comparison function decides when two
elements of the same type are equal.*/
extern int dict_DSTRUCT_init(dict *d, size_t elem_size, comp_fn_t comp);

/* Given a pointer to an element of the type the dictionary holds, return a
 * pointer to the element in the dictionary whose key matches the key of the
 * given element, if one exists. The key of the element is defined by
 * the comparison function. The function signature differs from the one given in
 * the book (pg. 72), but if I use the element and not it's key I don't have to
 * have two comparison functions, one for the element and one for the element's
 * key. */
extern void *dict_DSTRUCT_search(dict *d, void *elem_addr);

/* Given a pointer to an element of the type the dictionary holds, insert the
 * element in the dictionary. */
extern int dict_DSTRUCT_insert(dict *d, void *elem_addr);

/* Given a pointer to an element already in the dictionary, remove it from the
 * dictionary. */
extern void dict_DSTRUCT_delete(dict *d, void *dict_elem_addr);

/* Retrieve the item with the largest (or smallest) key from the dictionary. */
extern void *dict_DSTRUCT_max(dict *d);
extern void *dict_DSTRUCT_min(dict *d);

/* Retrieve the item from the dictionary whose key is immediately before (or
 * after) the element in sorted order. The key is defined by the comp function*/
extern void *dict_DSTRUCT_predecessor(dict *d, void *elem_addr);
extern void *dict_DSTRUCT_successor(dict *d, void *elem_addr);

/* Cleanup the dictionary when it's no longer needed. */
extern int *dict_DSTRUCT_destroy(dict *d);

#endif // DICT_H

/* Map generic dictionary interfaces to specific implementation. */
#define dict_init dict_DSTRUCT_init
#define dict_search dict_DSTRUCT_search
#define dict_insert dict_DSTRUCT_insert
#define dict_remove dict_DSTRUCT_remove
#define dict_max dict_DSTRUCT_max
#define dict_min dict_DSTRUCT_min
#define dict_predecessor dict_DSTRUCT_predecessor
#define dict_successor dict_DSTRUCT_successor
#define dict_destroy dict_DSTRUCT_destroy
