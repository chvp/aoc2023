#include <string.h>

#include "../lib/input.h"


int get_number(char* line) {
  line += 5; // Skip "Game "
  char *read_to = NULL;
  int id = strtol(line, &read_to, 10);
  line = read_to;
  while (*line != '\n') {
    line += 2;
    int count = strtol(line, &read_to, 10);
    line = read_to;
    switch(line[1]) {
    case 'r':
      if (count > 12) {
        return 0;
      }
      line += 4;
      break;
    case 'g':
      if (count > 13) {
        return 0;
      }
      line += 6;
      break;
    case 'b':
      if (count > 14) {
        return 0;
      }
      line += 5;
      break;
    }
  }
  return id;
}


int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;
  ssize_t read = 0;

  int sum = 0;
  while ((read = getline(&line, &len, input)) != -1) {
    sum += get_number(line);
  }
  free(line);

  printf("%d\n", sum);

  return 0;
}
