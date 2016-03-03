#include <stdio.h>
#include "ex_ch03.h"
#include "stack.h"

void ex_03_01(char *parens) {
	stack *s = NULL;
	char c;
	int pos = 0;

	printf("%s\n", parens);
	while ((c = *parens++) != '\0' && ++pos) {
		if (c == '(')
			stack_push(&s, c);
		else if (c == ')') {
			if (s == NULL || stack_size(s) == 0) {
				printf("wrong parens at pos %d\n", pos);
				break;
			} else
				stack_pop(&s);
		}
		else {
			printf("wrong char, %c at %d\n", c, pos);
			break;
		}
	}
}

