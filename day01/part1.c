#include <string.h>

#include "../lib/input.h"

int get_number(char* line) {
  int first_digit = -1;
  int last_digit = -1;
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] >= '0' && line[i] <= '9') {
      if (first_digit == -1) {
        first_digit = line[i] - '0';
      }
      last_digit = line[i] - '0';
    }
  }
  return 10 * first_digit + last_digit;
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
