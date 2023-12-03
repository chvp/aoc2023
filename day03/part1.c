#include <string.h>

#include "../lib/input.h"

int is_symbol(char* line, ssize_t len, int index) {
  if (line != NULL &&
      index >= 0 &&
      index < len - 1 &&
      line[index] != '.' &&
      (line[index] < '0' || line[index] > '9')
      ) {
    return 1;
  }
  return 0;
}

int get_number(char* previous, char* line, char* next, ssize_t len) {
  int sum = 0;
  int i = 0;
  while (i < len - 1) {
    if (line[i] >= '0' && line[i] <= '9') {
      char* read_to = NULL;
      int num = strtol(line + i, &read_to, 10);
      int length = read_to - (line + i);
      int should_add = 0;
      for (int j = i - 1; j < i + length + 1; j++) {
        should_add |= is_symbol(previous, len, j);
        should_add |= is_symbol(line, len, j);
        should_add |= is_symbol(next, len, j);
      }
      if (should_add != 0) {
        sum += num;
      }
      i += length;
    } else {
      i += 1;
    }
  }
  return sum;
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *previous = NULL;
  char *line = NULL;
  char *next = NULL;
  size_t len = 0;
  ssize_t read = 0;

  int sum = 0;
  read = getline(&line, &len, input);
  len = 0;
  while (getline(&next, &len, input) != -1) {
    sum += get_number(previous, line, next, read);
    free(previous);
    previous = line;
    line = next;
    next = NULL;
    len = 0;
  }
  sum += get_number(previous, line, NULL, read);

  free(previous);
  free(line);
  free(next);

  printf("%d\n", sum);

  return 0;
}
