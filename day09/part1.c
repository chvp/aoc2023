#include <string.h>

#include "../lib/input.h"
#include "../lib/arraylist.h"

long get_next(arraylist *values) {
  int num_zeros = 0;
  long result = 0;
  while (num_zeros != values->count) {
    result += values->buffer[values->count - 1];
    arraylist new = arraylist_init();
    num_zeros = 0;
    for (int i = 1; i < values->count; i++) {
      long val = values->buffer[i] - values->buffer[i - 1];
      arraylist_add(&new, val);
      if (val == 0) { num_zeros++; }
    }
    arraylist_free(values);
    *values = new;
  }
  return result;
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;

  long result = 0;
  while (getline(&line, &len, input) != -1) {
    arraylist numbers = arraylist_init();
    char *current = line;
    while (*current != '\n') {
      arraylist_add(&numbers, strtol(current, &current, 10));
    }
    result += get_next(&numbers);
    arraylist_free(&numbers);
  }
  free(line);

  printf("%ld\n", result);

  return 0;
}
