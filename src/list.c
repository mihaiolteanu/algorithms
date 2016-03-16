#include <string.h>
#include <stdio.h>
#include "list.h"
#include "system.h"

void list_init(list *l, size_t elem_size) {
	l->tsize = elem_size;
	l->head = NULL;
}

int list_add(list *l, void *elem_addr) {
	size_t tsize = l->tsize;

	list_node *node = malloc(sizeof(list_node) + tsize);
	if (node == NULL)
		return ERROR;
	memcpy((char *)&node->data, (char *)elem_addr, tsize);
	node->next = l->head;
	l->head = node;
	return OK;
}

void *list_search(list *l, void *src_addr, size_t struct_pos, size_t elem_size) {
	list_node *node = l->head;

	while(node != NULL) {
		char *data = node->data;
		char *elem = data + struct_pos;
		int same = strncmp((char *)src_addr,
				   elem, elem_size);
		if (same == 0)
			return data;
		node = node->next;
	}
	return NULL;
}
