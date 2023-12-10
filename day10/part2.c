#include <string.h>

#include "../lib/input.h"
#include "../lib/arraylist.h"

void flood(char *flooded, char *grid, int width, int height) {
  arraylist todo = arraylist_init();
  arraylist_add(&todo, 0);
  flooded[0] = 1;
  while(todo.count > 0) {
    int pos = arraylist_pop(&todo);
    if (pos - 1 > 0 && flooded[pos - 1] == 0 && grid[pos - 1] == 0)  {
      flooded[pos - 1] = 1;
      arraylist_add(&todo, pos - 1);
    }
    if (pos - width > 0 && flooded[pos - width] == 0 && grid[pos - width] == 0)  {
      flooded[pos - width] = 1;
      arraylist_add(&todo, pos - width);
    }
    if (pos + width < width * height && flooded[pos + width] == 0 && grid[pos + width] == 0) {
      flooded[pos + width] = 1;
      arraylist_add(&todo, pos + width);
    }
    // When at the end of a line, this wraps around to the next line, but since the entire outer border will be filled anyway, who cares?
    if (pos + 1 < width * height && flooded[pos + 1] == 0 && grid[pos + 1] == 0) {
      flooded[pos + 1] = 1;
      arraylist_add(&todo, pos + 1);
    }
  }
}

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
  char *grid = malloc(width * 9 * sizeof(char));
  int pos = 0;
  for (int i = 0; i < width; i++) {
    grid[i * 3] = '.';
    grid[i * 3 + 1] = line[i] == '|' || line[i] == 'L' || line[i] == 'J' ? '|' : '.';
    grid[i * 3 + 2] = '.';
    grid[width * 3 + i * 3] = line[i] == '-' || line[i] == 'J' || line[i] == '7' ? '-' : '.';
    grid[width * 3 + i * 3 + 1] = line[i];
    grid[width * 3 + i * 3 + 2] = line[i] == '-' || line[i] == 'F' || line[i] == 'L' ? '-' : '.';
    grid[width * 6 + i * 3] = '.';
    grid[width * 6 + i * 3 + 1] = line[i] == '|' || line[i] == 'F' || line[i] == '7' ? '|' : '.';
    grid[width * 6 + i * 3 + 2] = '.';
    if (line[i] == 'S') {
      pos = width * 3 + i * 3 + 1;
      int num = 0;
      if (i > 0 && (line[i - 1] == '-' || line[i - 1] == 'F' || line[i - 1] == 'L')) {
        grid[width * 3 + i * 3] = '-';
        num++;
      }
      if (i < width - 1 && (line[i + 1] == '-' || line[i + 1] == 'J' || line[i + 1] == '7')) {
        grid[width * 3 + i * 3 + 2] = '-';
        num++;
      }
      if (num < 2) {
        grid[width * 6 + i * 3 + 1] = '|';
      }
    }
  }

  while (getline(&line, &len, input) != -1) {
    grid = realloc(grid, width * (height + 1) * 9 * sizeof(char));
    for (int i = 0; i < width; i++) {
      grid[height * width * 9 + i * 3] = '.';
      grid[height * width * 9 + i * 3 + 1] = line[i] == '|' || line[i] == 'L' || line[i] == 'J' ? '|' : '.';
      grid[height * width * 9 + i * 3 + 2] = '.';
      grid[height * width * 9 + width * 3 + i * 3] = line[i] == '-' || line[i] == 'J' || line[i] == '7' ? '-' : '.';
      grid[height * width * 9 + width * 3 + i * 3 + 1] = line[i];
      grid[height * width * 9 + width * 3 + i * 3 + 2] = line[i] == '-' || line[i] == 'F' || line[i] == 'L' ? '-' : '.';
      grid[height * width * 9 + width * 6 + i * 3] = '.';
      grid[height * width * 9 + width * 6 + i * 3 + 1] = line[i] == '|' || line[i] == 'F' || line[i] == '7' ? '|' : '.';
      grid[height * width * 9 + width * 6 + i * 3 + 2] = '.';
      if (line[i] == 'S') {
        pos = height * width * 9 + width * 3 + i * 3 + 1;
        int num = 0;
        if (grid[(height - 1) * width * 9 + width * 6 + i * 3 + 1] == '|') {
          grid[height * width * 9 + i * 3 + 1] = '|';
          num++;
        }
        if (i > 0 && (line[i - 1] == '-' || line[i - 1] == 'F' || line[i - 1] == 'L')) {
          grid[height * width * 9 + width * 3 + i * 3] = '-';
          num++;
        }
        if (i < width - 1 && (line[i + 1] == '-' || line[i + 1] == 'J' || line[i + 1] == '7')) {
          grid[height * width * 9 + width * 3 + i * 3 + 2] = '-';
          num++;
        }
        if (num < 2) {
          grid[height * width * 9 + width * 6 + i * 3 + 1] = '|';
        }
      }
    }
    height++;
  }
  free(line);

  height *= 3;
  width *= 3;

  char *visited = calloc(width * height, sizeof(char));
  visited[pos] = 1;
  int prev = pos;
  if (grid[pos + 1] == '-' || grid[pos + 1] == 'J' || grid[pos + 1] == '7') {
    pos += 1;
  } else if (grid[pos + width] == '|' || grid[pos + width] == 'L' || grid[pos + width] == 'J') {
    pos += width;
  } else if (grid[pos - width] == '|' || grid[pos - width] == '7' || grid[pos - width] == 'F') {
    pos -= width;
  }
  while (grid[pos] != 'S') {
    visited[pos] = 1;
    int newpos = step(grid, prev, pos, width);
    prev = pos;
    pos = newpos;
  }

  char *flooded = calloc(width * height, sizeof(char));
  flood(flooded, visited, width, height);

  int emptycount = 0;
  for (int i = 0; i < height / 3; i++) {
    for (int j = 0; j < width / 3; j++) {
      int num = 0;
      for (int ii = 0; ii < 3; ii++) {
        for (int jj = 0; jj < 3; jj++) {
          num += flooded[(i * 3 + ii) * width + j * 3 + jj];
        }
      }
      if (num == 0) { emptycount += 1; };
    }
  }

  printf("%d\n", emptycount);
  
  free(flooded);
  free(grid);

  return 0;
}
