#include <string.h>
#include <limits.h>

#include "../lib/input.h"
#include "../lib/treeset.h"

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
  return count;
}


int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  int* counts = calloc(256, sizeof(int));
  int size = 256;

  char *line = NULL;
  size_t len = 0;

  int sum = 0;
  int i = 0;
  while (getline(&line, &len, input) != -1) {
    if (i >= size) {
      counts = realloc(counts, size * 2 * sizeof(int));
      for (int j = size; j < size * 2; j++) {
        counts[j] = 0;
      }
      size *= 2;
    }
    counts[i]++;
    sum += counts[i];
    int count = get_number(line);
    for (int j = i + 1; j < i + count + 1; j++) {
      if (j >= size) {
        counts = realloc(counts, size * 2 * sizeof(int));
        for (int k = size; k < size * 2; k++) {
          counts[k] = 0;
        }
        size *= 2;
      }
      counts[j] += counts[i];
    }
    i += 1;
  }
  free(line);
  free(counts);

  printf("%d\n", sum);

  return 0;
}
