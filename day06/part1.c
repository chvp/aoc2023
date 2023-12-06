#include <string.h>

#include "../lib/input.h"

#include "common.c"

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *timeline = NULL;
  size_t len = 0;
  getline(&timeline, &len, input);
  char *timestart = timeline + 10;

  char *recordline = NULL;
  len = 0;
  getline(&recordline, &len, input);
  char *recordstart = recordline + 10;

  long num = 1;

  while (*timestart != '\n') {
    long time = strtol(timestart, &timestart, 10);
    long record = strtol(recordstart, &recordstart, 10);
    num *= get_interval(time, record);
  }

  free(timeline);
  free(recordline);
  printf("%ld\n", num);

  return 0;
}
