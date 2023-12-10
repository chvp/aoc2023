#include <string.h>

#include "../lib/input.h"

int step(char *grid, int prev, int pos, int width) {
  switch(grid[pos]) {
  case '|':
    return prev < pos ? pos + width : pos - width;
  case '-':
    return prev < pos ? pos + 1 : pos - 1;
  case 'L':
    return prev < pos ? pos + 1 : pos - width;
  case 'J':
    return prev + 1 == pos ? pos - width : pos - 1;
  case '7':
    return prev < pos ? pos + width : pos - 1;
  case 'F':
    return prev - 1 == pos ? pos + width : pos + 1;
  }
  printf("Unknown pipe '%c'", grid[pos]);
  exit(1);
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;

  ssize_t read = getline(&line, &len, input);
  int width = read - 1;
  int height = 1;
  char *grid = malloc(width * sizeof(char));
  int pos = 0;
  for (int i = 0; i < width; i++) {
    grid[i] = line[i];
    if (line[i] == 'S') {
      pos = i;
    }
  }

  while (getline(&line, &len, input) != -1) {
    grid = realloc(grid, width * (height + 1) * sizeof(char));
    for (int i = 0; i < width; i++) {
      grid[height * width + i] = line[i];
      if (line[i] == 'S') {
        pos = width * height + i;
      }
    }
    height++;
  }
  free(line);

  int count = 1;
  int prev = pos;
  if (grid[pos - width] == '|' || grid[pos - width] == '7' || grid[pos - width] == 'F') {
    pos -= width;
  } else if (grid[pos + 1] == '-' || grid[pos + 1] == 'J' || grid[pos + 1] == '7') {
    pos += 1;
  } else if (grid[pos + width] == '|' || grid[pos + width] == 'L' || grid[pos + width] == 'J') {
    pos += width;
  }
  while (grid[pos] != 'S') {
    count++;
    int newpos = step(grid, prev, pos, width);
    prev = pos;
    pos = newpos;
  }

  printf("%d\n", count / 2);
  
  free(grid);

  return 0;
}
