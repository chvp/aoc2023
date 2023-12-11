#include <string.h>

#include "../lib/input.h"
#include "../lib/arraylist.h"
#include "../lib/treeset.h"

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  int y_offset = 0;
  int max_x = 0;
  arraylist xs = arraylist_init();
  arraylist ys = arraylist_init();
  treeset encountered = treeset_init();

  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, input) != -1) {
    int i = 0;
    int num = 0;
    while (line[i] != '\n') {
      if (line[i] == '#') {
        arraylist_add(&xs, i);
        arraylist_add(&ys, y_offset);
        treeset_add(&encountered, i);
        num++;
        if (i > max_x) {
          max_x = i;
        }
      }
      i++;
    }
    y_offset++;
    if (num == 0) { y_offset++; }
  }
  free(line);

  int *offsets = malloc((max_x + 1) * sizeof(int));
  int x_offset = 0;
  for (int i = 0; i < max_x + 1; i++) {
    if (treeset_has(&encountered, i) == 0) {
      x_offset++;
    }
    offsets[i] = x_offset;
  }
  treeset_free(&encountered);
  for (int i = 0; i < xs.count; i++) {
    xs.buffer[i] += offsets[xs.buffer[i]];
  }
  free(offsets);

  long result = 0;
  for (int i = 0; i < xs.count; i++) {
    for (int j = i + 1; j < xs.count; j++) {
      result += labs(xs.buffer[i] - xs.buffer[j]) + labs(ys.buffer[i] - ys.buffer[j]);
    }
  }

  arraylist_free(&xs);
  arraylist_free(&ys);

  printf("%ld\n", result);

  return 0;
}
