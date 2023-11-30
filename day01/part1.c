#include <string.h>

#include "../lib/input.h"

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;
  ssize_t read = 0;

  int max = 0;
  int curr = 0;
  while ((read = getline(&line, &len, input)) != -1) {
    if (strlen(line) > 1) {
      curr += atoi(line);
    } else {
      curr = 0;
    }
    if (curr > max) {
      max = curr;
    }
  }
  free(line);

  printf("%d\n", max);

  return 0;
}
