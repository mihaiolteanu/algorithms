#include "list.h"
#include "list_int.h"

void list_int_init(list *l) {
	list_init(l, sizeof(int));
}

int list_int_add(list *l, int elem) {
	return list_add(l, &elem);
}

// return the address if found, null otherwise
int *list_int_search(list *l, int elem) {
	return (int *)list_search(l, &elem, 0, sizeof(int));
}
