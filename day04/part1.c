#include <string.h>
#include <limits.h>

#include "../lib/input.h"

typedef struct treeset {
  int capacity;
  int *buffer;
} treeset;

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

int get_number(char* line) {
  // Skip heading, id and colon
  line += 5;
  char *read_to = NULL;
  strtol(line, &read_to, 10);
  line = read_to;
  line += 2;

  treeset s = treeset_init();

  while (*line != '|') {
    int num = strtol(line, &read_to, 10);
    treeset_add(&s, num);
    line = read_to + 1;
  }
  int count = 0;
  line += 2;
  while (*line != '\n') {
    int num = strtol(line, &read_to, 10);
    count += treeset_has(&s, num);
    line = read_to;
  }

  treeset_free(&s);
  if (count > 0) {
    return 1 << (count - 1);
  } else {
    return 0;
  }
}


int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;

  int sum = 0;
  while (getline(&line, &len, input) != -1) {
    sum += get_number(line);
  }
  free(line);

  printf("%d\n", sum);

  return 0;
}
