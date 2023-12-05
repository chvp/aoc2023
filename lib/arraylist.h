#ifndef AOC_ARRAYLIST_H
#define AOC_ARRAYLIST_H

#include <stdlib.h>

typedef struct arraylist {
  int capacity;
  int count;
  long *buffer;
} arraylist;

arraylist arraylist_init();
void arraylist_add(arraylist *l, long val);
void arraylist_free(arraylist *l);

#endif
