#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int breaker(FILE * f) {
  int fre[26];
  for (int i = 0; i < 26; i++) {
    fre[i] = 0;
  }
  int maxFre = 0;
  int key = 0;
  int temp;
  while ((temp = fgetc(f)) != EOF) {
    if (isalpha(temp)) {
      int index = tolower(temp) - 'a';
      fre[index]++;
      if (fre[index] > maxFre) {
        maxFre = fre[index];
        key = (index + 22) % 26;
      }
    }
  }
  if (maxFre == 0) {
    fprintf(stderr, "Invalid input");
    exit(EXIT_FAILURE);
  }
  return key;
}

int main(int argc, char * argv[]) {
  FILE * f;

  if (argc != 2) {
    fprintf(stderr, "Usage %s file\n", argv[0]);
    return EXIT_FAILURE;
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open %s file\n", argv[1]);
    return EXIT_FAILURE;
  }

  int key = breaker(f);
  printf("%d\n", key);
  int j = fclose(f);
  if (j != 0) {
    perror("failed close");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
