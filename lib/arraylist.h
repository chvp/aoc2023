#ifndef AOC_ARRAYLIST_H
#define AOC_ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct arraylist {
  int capacity;
  int count;
  long *buffer;
} arraylist;

arraylist arraylist_init();
void arraylist_add(arraylist *l, long val);
long arraylist_pop(arraylist *l);
void arraylist_free(arraylist *l);

#endif
