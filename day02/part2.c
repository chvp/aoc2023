#include <string.h>

#include "../lib/input.h"


int get_number(char* line) {
  line += 5; // Skip "Game "
  char *read_to = NULL;
  strtol(line, &read_to, 10);
  line = read_to;
  int maxr = 0;
  int maxg = 0;
  int maxb = 0;
  while (*line != '\n') {
    line += 2;
    int count = strtol(line, &read_to, 10);
    line = read_to;
    switch(line[1]) {
    case 'r':
      if (count > maxr) {
        maxr = count;
      }
      line += 4;
      break;
    case 'g':
      if (count > maxg) {
        maxg = count;
      }
      line += 6;
      break;
    case 'b':
      if (count > maxb) {
        maxb = count;
      }
      line += 5;
      break;
    }
  }
  return maxr * maxg * maxb;
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
