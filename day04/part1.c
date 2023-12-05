#include <string.h>

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
