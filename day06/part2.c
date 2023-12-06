#include <string.h>

#include "../lib/input.h"

#include "common.c"

long get_number(char *s) {
  long num = 0;
  while (*s != '\n') {
    if (*s >= '0' && *s <= '9') {
      num = num * 10 + *s - '0';
    }
    s++;
  }
  return num;
}

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

  long time = get_number(timestart);
  long record = get_number(recordstart);

  free(timeline);
  free(recordline);

  printf("%ld\n", get_interval(time, record));

  return 0;
}
