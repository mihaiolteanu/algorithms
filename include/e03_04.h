#ifndef E03_04H
#define E03_04H

#define E03_04FREE 0
#define E03_04USED 1
#define E03_04RESET 0
#define E03_04SET 1

typedef struct {
	int size;
	int *a;
} e03_04dict;

extern int e03_04dict_init(e03_04dict *d, int size);
extern int e03_04dict_search(e03_04dict *d, int value);
extern int e03_04dict_insert(e03_04dict *d, int value);
extern int e03_04dict_delete(e03_04dict *d, int value);

#endif // E03_04H
