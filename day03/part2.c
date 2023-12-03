#include <string.h>

#include "../lib/input.h"

void look_for_numbers(char* line, int i, int* num_count, int* to_add) {
  int j = i;
  while (j > 0 && line[j - 1] >= '0' && line[j - 1] <= '9') {
    j--;
  }
  while (j <= i + 1) {
    if (line[j] >= '0' && line[j] <= '9') {
      char *read_to = NULL;
      int num = strtol(line + j, &read_to, 10);
      *to_add *= num;
      *num_count += 1;
      j = (read_to - line);
    } else {
      j += 1;
    }
  }
}

int get_number(char* previous, char* line, char* next, ssize_t len) {
  int sum = 0;
  int i = 0;
  while (i < len - 1) {
    if (line[i] == '*') {
      int num_count = 0;
      int to_add = 1;
      if (previous != NULL) {
        look_for_numbers(previous, i, &num_count, &to_add);
      }
      look_for_numbers(line, i, &num_count, &to_add);
      if (next != NULL) {
        look_for_numbers(next, i, &num_count, &to_add);
      }
      if (num_count == 2) {
        sum += to_add;
      }
    }
    i += 1;
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
