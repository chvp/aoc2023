#include <string.h>

#include "../lib/input.h"

char *digits[] = {
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
  "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

size_t lengths[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  4, 3, 3, 3, 4, 4, 3, 5, 5, 4
};

int get_number(char* line) {
  size_t llen = strlen(line);
  int first_digit = -1;
  int last_digit = -1;
  for (int i = 0; i < llen; i++) {
    for (int j = 0; j < 20; j++) {
      if (llen - i >= lengths[j] && memcmp(line + i, digits[j], lengths[j]) == 0) {
        if (first_digit == -1) {
          first_digit = j % 10;
        }
        last_digit = j % 10;
      }
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
