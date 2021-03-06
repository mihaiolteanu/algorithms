#include "hash.h"
#include "unity.h"

static unsigned long string_hash(char **str);
static int string_comp_pointers(const char *a, const char *b);

void test_hash_search() {
	hash_table h;
	char *str;
	char *what = "what";
	char *ever = "ever";

	hash_init(&h, sizeof(char *),
		  (hash_fn_t)string_hash,
		  (comp_fn_t)string_comp_pointers, 100);
	hash_insert(&h, &what);
	hash_insert(&h, &ever);

	str = *(char**)hash_search(&h, &what);

	if (str != NULL)
	        TEST_ASSERT_EQUAL_STRING(str, "what");
                
	else
	        TEST_ASSERT_TRUE_MESSAGE(0, "hash search returned NULL");
	
	hash_destroy(&h);
}

static unsigned long string_hash(char **str) {
	unsigned long hash_res = 5381;
	int c;
	char *strp = *str;

	/* djb2 algorithm. */
	while ((c = *strp++))
		hash_res = ((hash_res << 5) + hash_res) + c; /* hash * 33 + c */
	return hash_res;
}

static int string_comp_pointers(const char *a, const char *b) {
	char **ap = (char **)a;
	char **bp = (char **)b;
	
	if (*ap == *bp)
		return 0;
	return 1;
}
