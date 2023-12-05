#include "arraylist.h"

arraylist arraylist_init() {
  arraylist val;
  val.count = 0;
  val.capacity = 32;
  val.buffer = calloc(val.capacity, sizeof(long));
  return val;
}

void arraylist_add(arraylist *l, long val) {
  if (l->count >= l->capacity) {
    l->buffer = realloc(l->buffer, l->capacity * 2 * sizeof(long));
    l->capacity *= 2;
  }
  l->buffer[l->count++] = val;
}

void arraylist_free(arraylist *l) {
  free(l->buffer);
  l->capacity = 0;
  l->count = 0;
}
