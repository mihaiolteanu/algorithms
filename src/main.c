#include <stdio.h>
#include <assert.h>
#include "array.h"
#include "stack.h"
#include "list.h"
#include "ex_ch03.h"

static void print_list(list *l);

typedef struct city_t {
	size_t size;
	size_t pop;
} city;

int main(void) {
	list l;
	city re = { 24, 34 };
	city si = { 55, 150 };

	list_init(&l, sizeof(city));
	list_add(&l, &re);
	list_add(&l, &si);

	city *result = list_search(&l, &si,
				   (char *)&si.pop - (char *)&si.size,
				   sizeof(si.pop));
	if (result == NULL)
		printf("%d not found\n", si.pop);
	else
		printf("size: %d, pop: %d\n", result->size, result->pop);
//		printf("%d found at %p\n", si.pop, result);



/*
	list l;

	list_init(&l, sizeof(int));
	for (int i = 1; i < 10; i++)
		list_add(&l, &i);
	print_list(&l);

	int search = 5;
	list_node *result = list_search(&l, &search, 0, sizeof(int));

	if (result == NULL)
		printf("%d not found\n", search);
	else
		printf("%d found at %p\n", search, result);
*/
	return 0;

}

static void print_list(list *l) {
	list_node *node = l->head;
	
	while (node != NULL) {
		printf("%d ", *(int *)node->data);
		node = node->next;
	}
	printf("\n");
}
