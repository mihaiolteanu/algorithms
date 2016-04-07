#include <string.h>
#include <stdio.h>
#include "list.h"
#include "system.h"

// Find if elem_size of bytes at src_addr are equal to elem_size of bytes
// starting at struct_pos bytes past the node.
static int elem_compare(void *src_addr, list_node *node, size_t struct_pos, size_t elem_size);
// Free the memory allocated for node.
static void node_free(list_node *node);
// Helper function to recursively reverse a linked list. To be used in a helper
// function
static void list_reverse_rec_local(list *l, list_node *prev, list_node *node);
// Given a node, deallocate it and all the nodes that are linked to it.
static void deallocate_all_nodes(list_node *node);

void list_init(list *l, size_t elem_size, comp_fn_t comp) {
	l->tsize = elem_size;
	l->comp = comp;
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

void *list_search(list *l, void *src_addr) {
	list_node *node = l->head;
	comp_fn_t comp = l->comp;

	while(node != NULL) {
		if (comp(src_addr, node->data) == 0)
			return node->data;
		node = node->next;
	}
	return NULL;
}

void list_remove(list *l, void *src_addr) {
	list_node **nodepp = &l->head;
	comp_fn_t comp = l->comp;

	while(*nodepp != NULL) {
		if (comp(src_addr, (*nodepp)->data) == 0) {
			list_node *old_elem = *nodepp;
			*nodepp = (*nodepp)->next; // Relink
			node_free(old_elem);
			return;
		}
		nodepp = &(*nodepp)->next;
	}
	return;
}

/* 3-2.
   solution for exercise 3-2 */
void list_reverse(list *l) {
	list_node *nodep = l->head; // First element
	list_node *prev = NULL;

	if (nodep == NULL)
		return; // Nothing to reverse.

	while (nodep != NULL) {
		list_node *next = nodep->next;
		nodep->next = prev;
		prev = nodep;
		nodep = next;
	}
	l->head = prev;
}

void list_destroy(list *l) {
	list_node *head = l->head;

	deallocate_all_nodes(head);
}

static void deallocate_all_nodes(list_node *node) {
	if (node != NULL)
		deallocate_all_nodes(node->next);
	free(node);
}

static void list_reverse_rec_local(list *l, list_node *prev, list_node *node) {
	if (node == NULL)
		return; // Nothing to reverse
	l->head = node;
	if (node->next != NULL)
		list_reverse_rec_local(l, node, node->next);
	node->next = prev;
}

/* 3-2.
   recursive solution for exercise 3-2 */
void list_reverse_rec(list *l) {
	list_reverse_rec_local(l, NULL, l->head);
}

static void node_free(list_node *node) {
	free(node);
}

static int elem_compare(void *src_addr, list_node *node, size_t struct_pos, size_t elem_size) {
	char *data = node->data;
	char *elem = data + struct_pos;
	return strncmp((char *)src_addr,
		       elem, elem_size);
}


