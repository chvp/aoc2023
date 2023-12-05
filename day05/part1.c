#include <string.h>

#include "../lib/input.h"
#include "../lib/arraylist.h"

arraylist replace_numbers(arraylist numbers, arraylist froms, arraylist tos, arraylist lens) {
  arraylist new = arraylist_init();
  for (int i = 0; i < numbers.count; i++) {
    int j = 0;
    while (j < froms.count && (numbers.buffer[i] < froms.buffer[j] || numbers.buffer[i] >= froms.buffer[j] + lens.buffer[j])) {
      j++;
    }
    arraylist_add(&new, numbers.buffer[i] + (j < froms.count ? (tos.buffer[j] - froms.buffer[j]) : 0));
  }
  arraylist_free(&numbers);
  return new;
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;

  getline(&line, &len, input);
  arraylist numbers = arraylist_init();
  char *start = line + 7;
  while (*start != '\n') {
    arraylist_add(&numbers, strtol(start, &start, 10));
  }

  getline(&line, &len, input);
  getline(&line, &len, input);

  arraylist range_froms = arraylist_init();
  arraylist range_tos = arraylist_init();
  arraylist range_lens = arraylist_init();

  while (getline(&line, &len, input) != -1) {
    if (*line == '\n') {
      numbers = replace_numbers(numbers, range_froms, range_tos, range_lens);
      arraylist_free(&range_froms);
      arraylist_free(&range_tos);
      arraylist_free(&range_lens);
      range_froms = arraylist_init();
      range_tos = arraylist_init();
      range_lens = arraylist_init();
      getline(&line, &len, input);
    } else {
      start = line;
      arraylist_add(&range_tos, strtol(start, &start, 10));
      arraylist_add(&range_froms, strtol(start, &start, 10));
      arraylist_add(&range_lens, strtol(start, &start, 10));
    }
  }
  numbers = replace_numbers(numbers, range_froms, range_tos, range_lens);
  free(line);
  arraylist_free(&range_froms);
  arraylist_free(&range_tos);
  arraylist_free(&range_lens);

  long num = numbers.buffer[0];
  for (int i = 1; i < numbers.count; i++) {
    if (numbers.buffer[i] < num) {
      num = numbers.buffer[i];
    }
  }

  printf("%ld\n", num);

  return 0;
}
