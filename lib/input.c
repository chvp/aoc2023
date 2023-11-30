#include "input.h"

FILE* get_file(int argc, char** argv) {
  if (argc != 4) {
    fprintf(stderr, "usage: %s <day> <part> <input>\n", argv[0]);
    exit(1);
  }
  FILE* input = fopen(argv[3], "r");
  if (input == NULL) {
    fprintf(stderr, "could not open '%s' for reading\n", argv[3]);
    exit(1);
  }
  return input;
}
