#include <string.h>

#include "../lib/input.h"
#include "../lib/arraylist.h"

long gcd(long i, long j) {
  while (j != 0) {
    long tmp = j;
    j = i % j;
    i = tmp;
  }
  return i;
}

long lcm(long i, long j) {
  return (i * j) / gcd(i > j ? i : j, i > j ? j : i);
}

int triple_to_int(char* start) {
  int result = 0;
  for (int i = 0; i < 3; i++) {
    result = result * 26 + start[i] - 'A';
  }
  return result;
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *instructions = NULL;
  size_t len = 0;
  getline(&instructions, &len, input);

  char *line = NULL;
  len = 0;

  int *graph = calloc(26 * 26 * 26 * 2, sizeof(int));

  arraylist currents = arraylist_init();

  getline(&line, &len, input);
  while(getline(&line, &len, input) != -1) {
    int index = triple_to_int(line);
    int left = triple_to_int(line + 7);
    int right = triple_to_int(line + 12);
    graph[index * 2] = left;
    graph[index * 2 + 1] = right;
    if (index % 26 == 0) {
      arraylist_add(&currents, index);
    }
  }
  free(line);

  long result = 1;
  for (int i = 0; i < currents.count; i++) {
    int current = currents.buffer[i];
    int index = 0;
    int count = 0;
    while (current % 26 != 25) {
      if (instructions[index] == '\n') {
        index = 0;
      }
      current = graph[2 * current + (instructions[index++] == 'L' ? 0 : 1)];
      count++;
    }
    result = lcm(result, count);
  }

  free(instructions);
  printf("%ld\n", result);

  return 0;
}
