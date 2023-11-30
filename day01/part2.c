#include <string.h>

#include "../lib/input.h"

void update_maxs(int* maxs, int new) {
  if (new > maxs[0]) {
      maxs[2] = maxs[1];
      maxs[1] = maxs[0];
      maxs[0] = new;
    } else if (new > maxs[1]) {
      maxs[2] = maxs[1];
      maxs[1] = new;
    } else if (new > maxs[2]) {
      maxs[2] = new;
    }
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  int maxs[] = {0, 0, 0};
  int curr = 0;

  char *line = NULL;
  size_t len = 0;
  ssize_t read = 0;
  while ((read = getline(&line, &len, input)) != -1) {
    if (strlen(line) > 1) {
      curr += atoi(line);
    } else {
      update_maxs(maxs, curr);
      curr = 0;
    }
  }
  update_maxs(maxs, curr);
  free(line);

  printf("%d\n", maxs[2] + maxs[1] + maxs[0]);

  return 0;
}
