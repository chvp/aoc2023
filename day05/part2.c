#include <string.h>

#include "../lib/input.h"
#include "../lib/arraylist.h"

#define MIN(x, y) ((x < y) ? (x) : (y))

int overlaps(long from1, long len1, long from2, long len2) {
  return (from1 <= from2 && from1 + len1 > from2) || (from2 <= from1 && from2 + len2 > from1);
}

void replace_numbers(arraylist *num_froms, arraylist *num_lens, arraylist froms, arraylist tos, arraylist lens) {
  arraylist new_froms = arraylist_init();
  arraylist new_lens = arraylist_init();
  for (int i = 0; i < num_froms->count; i++) {
    int j = 0;
    while (j < froms.count && !overlaps(num_froms->buffer[i], num_lens->buffer[i], froms.buffer[j], lens.buffer[j])) {
      j++;
    }
    // No, I'm not proud of this. Please don't look.
    if (j >= froms.count) {
      arraylist_add(&new_froms, num_froms->buffer[i]);
      arraylist_add(&new_lens, num_lens->buffer[i]);
    } else if (num_froms->buffer[i] == froms.buffer[j]) {
      arraylist_add(&new_froms, tos.buffer[j]);
      arraylist_add(&new_lens, MIN(num_lens->buffer[i], lens.buffer[j]));
      if (num_lens->buffer[i] > lens.buffer[j]) {
        arraylist_add(num_froms, num_froms->buffer[i] + lens.buffer[j]);
        arraylist_add(num_lens, num_lens->buffer[i] - lens.buffer[j]);
      }
    } else if (num_froms->buffer[i] < froms.buffer[j]) {
      arraylist_add(num_froms, num_froms->buffer[i]);
      arraylist_add(num_lens, froms.buffer[j] - num_froms->buffer[i]);
      if (num_froms->buffer[i] + num_lens->buffer[i] <= froms.buffer[j] + lens.buffer[j]) {
        arraylist_add(&new_froms, tos.buffer[j]);
        arraylist_add(&new_lens, num_lens->buffer[i] - (froms.buffer[j] - num_froms->buffer[i]));
      } else {
        arraylist_add(&new_froms, tos.buffer[j]);
        arraylist_add(&new_lens, lens.buffer[j]);
        arraylist_add(num_froms, froms.buffer[j] + lens.buffer[j]);
        arraylist_add(num_lens, num_lens->buffer[i] - (froms.buffer[j] - num_froms->buffer[i]) - lens.buffer[j]);
      }
    } else if (froms.buffer[j] + lens.buffer[j] >= num_froms->buffer[i] + num_lens->buffer[i]) {
      arraylist_add(&new_froms, tos.buffer[j] + (num_froms->buffer[i] - froms.buffer[j]));
      arraylist_add(&new_lens, num_lens->buffer[i]);
    } else {
      arraylist_add(&new_froms, tos.buffer[j] + (num_froms->buffer[i] - froms.buffer[j]));
      arraylist_add(&new_lens, lens.buffer[j] - (num_froms->buffer[i] - froms.buffer[j]));
      arraylist_add(num_froms, froms.buffer[j] + lens.buffer[j]);
      arraylist_add(num_lens, num_lens->buffer[i] - (lens.buffer[j] - (num_froms->buffer[i] - froms.buffer[j])));
    }
  }
  arraylist_free(num_froms);
  arraylist_free(num_lens);
  *num_froms = new_froms;
  *num_lens = new_lens;
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;

  getline(&line, &len, input);
  arraylist num_froms = arraylist_init();
  arraylist num_lens = arraylist_init();
  char *start = line + 7;
  while (*start != '\n') {
    arraylist_add(&num_froms, strtol(start, &start, 10));
    arraylist_add(&num_lens, strtol(start, &start, 10));
  }

  getline(&line, &len, input);
  getline(&line, &len, input);

  arraylist range_froms = arraylist_init();
  arraylist range_tos = arraylist_init();
  arraylist range_lens = arraylist_init();

  while (getline(&line, &len, input) != -1) {
    if (*line == '\n') {
      replace_numbers(&num_froms, &num_lens, range_froms, range_tos, range_lens);
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
  replace_numbers(&num_froms, &num_lens, range_froms, range_tos, range_lens);

  free(line);
  arraylist_free(&range_froms);
  arraylist_free(&range_tos);
  arraylist_free(&range_lens);

  long num = num_froms.buffer[0];
  for (int i = 1; i < num_froms.count; i++) {
    if (num_froms.buffer[i] < num) {
      num = num_froms.buffer[i];
    }
  }

  arraylist_free(&num_froms);
  arraylist_free(&num_lens);

  printf("%ld\n", num);

  return 0;
}
