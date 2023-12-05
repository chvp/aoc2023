#include "treeset.h"

treeset treeset_init() {
  treeset val;
  val.capacity = 31;
  val.buffer = malloc(val.capacity * sizeof(int));
  for (int i = 0; i < 31; i++) {
    val.buffer[i] = INT_MIN;
  };
  return val;
}

void treeset_add(treeset* s, int val) {
  int index = 0;
  while (index < s->capacity && s->buffer[index] != INT_MIN) {
    if (val == s->buffer[index]) {
      return;
    } else if (val > s->buffer[index]) {
      index = index * 2 + 1;
    } else {
      index = index * 2 + 2;
    }
  }
  if (index >= s->capacity) {
    s->buffer = realloc(s->buffer, (s->capacity * 2 + 1) * sizeof(int));
    for (int i = s->capacity; i < s->capacity * 2 + 1; i++) {
      s->buffer[i] = INT_MIN;
    }
    s->capacity = s->capacity * 2 + 1;
  }
  s->buffer[index] = val;
}

int treeset_has(treeset *s, int val) {
  int index = 0;
  while (index < s->capacity && s->buffer[index] != INT_MIN) {
    if (val == s->buffer[index]) {
      return 1;
    } else if (val > s->buffer[index]) {
      index = index * 2 + 1;
    } else {
      index = index * 2 + 2;
    }
  }
  return 0;
}

void treeset_free(treeset *s) {
  free(s->buffer);
  s->capacity = 0;
}
