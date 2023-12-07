#include <string.h>

#include "../lib/input.h"
#include "../lib/arraylist.h"

int decode_card(char card) {
  if (card >= '2' && card <= '9') {
    return card - '1';
  }
  switch (card) {
  case 'A':
    return 12;
  case 'K':
    return 11;
  case 'Q':
    return 10;
  case 'J':
    return 0;
  case 'T':
    return 9;
  }
  printf("Invalid card %c\n", card);
  exit(1);
}

long type_from_counts(char* counts) {
  int twos = 0;
  int max = 0;
  int argmax = 0;
  for (int i = 1; i < 13; i++) {
    if (counts[i] > max) {
      max = counts[i];
      argmax = i;
    }
    if (counts[i] == 2) { twos++; }
  }
  switch (max + counts[0]) {
  case 5:
    return 6;
  case 4:
    return 5;
  case 3:
    if (twos == 2) {
      return 4;
    } else if (twos == 1 && counts[argmax] != 2) {
      return 4;
    } else {
      return 3;
    }
  case 2:
    if (twos == 2) {
      return 2;
    } else {
      return 1;
    }
  case 1:
    return 0;
  }
  printf("Invalid hand %d %d\n", max, twos);
  exit(1);
}

#include "common.c"
