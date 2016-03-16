/* list_int.h
   Linked list of ints implementation based on the generic one
*/

#ifndef LIST_INT_H
#define LIST_INT_H

#include "list.h"

extern void list_int_init(list *l);
extern  int list_int_add(list *l, int elem);
// return the address if found, null otherwise
extern int *list_int_search(list *l, int elem);

#endif // LIST_INT_H
