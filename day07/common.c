long decode_hand(char* line) {
  char counts[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  long result = 0;
  for (int i = 0; i < 5; i++) {
    result = result * 100 + decode_card(line[i]);
    counts[decode_card(line[i])]++;
  }
  result += type_from_counts(counts) * 10000000000;

  return result;
}

int main(int argc, char** argv) {
  FILE* input = get_file(argc, argv);

  char *line = NULL;
  size_t len = 0;

  arraylist hands = arraylist_init();
  arraylist bids = arraylist_init();

  while (getline(&line, &len, input) != -1) {
    arraylist_add(&hands, decode_hand(line));
    arraylist_add(&bids, atoi(line + 6));

  }
  free(line);

  int swapped = 0;
  do {
    swapped = 0;
    for (int i = 1; i < hands.count; i++) {
      if (hands.buffer[i - 1] > hands.buffer[i]) {
        long tmp = hands.buffer[i - 1];
        hands.buffer[i - 1] = hands.buffer[i];
        hands.buffer[i] = tmp;
        tmp = bids.buffer[i - 1];
        bids.buffer[i - 1] = bids.buffer[i];
        bids.buffer[i] = tmp;
        swapped++;
      }
    }
  } while (swapped != 0);

  long num = 0;
  for (int i = 0; i < bids.count; i++) {
    num += bids.buffer[i] * (i + 1);
  }

  arraylist_free(&hands);
  arraylist_free(&bids);

  printf("%ld\n", num);

  return 0;
}
