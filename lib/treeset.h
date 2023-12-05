#ifndef AOC_TREESET_H
#define AOC_TREESET_H

#include <limits.h>
#include <stdlib.h>

typedef struct treeset {
  int capacity;
  int *buffer;
} treeset;

treeset treeset_init();
void treeset_add(treeset* s, int val);
int treeset_has(treeset *s, int val);
void treeset_free(treeset *s);

#endif
