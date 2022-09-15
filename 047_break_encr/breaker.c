#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int breaker(FILE * f) {
  int fre[26];
  int maxFre = 0;
  int key = 0;
  while (fgetc(f) != EOF) {
    int index = fgetc(f) - 'a';
    fre[index]++;
    if (fre[index] > maxFre) {
      maxFre = fre[index];
      key = (index + 22) % 26;
    }
  }
  return key;
}

int main(int argc, char * argv[]) {
  FILE * f;

  if (argc != 2) {
    fprintf(stderr, "Usage %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open %s file\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  int key = breaker(f);
  printf("Successfully break the cipher! key is %d.\n", key);
  fclose(f);
  return EXIT_SUCCESS;
}
