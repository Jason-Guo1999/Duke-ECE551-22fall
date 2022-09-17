#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void Mysort(FILE * f) {
  char ** lines = malloc(sizeof(*lines));
  size_t lsize = 0;
  size_t numOflines = 0;
  char * l = 0;
  while (getline(&l, &lsize, f) >= 0) {
    lines = realloc(lines, (numOflines + 1) * (sizeof(*lines)));
    lines[numOflines] = l;
    numOflines++;
    l = 0;
  }
  sortData(lines, numOflines);
  for (int i = 0; i < (int)numOflines; i++) {
    printf("%s\n", lines[i]);
    free(lines[i]);
  }
  free(l);
  free(lines);
  return;
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    if (stdin == NULL) {
      fprintf(stderr, "falied to open stdin\n");
      exit(EXIT_FAILURE);
    }
    FILE * f = stdin;
    Mysort(f);
    if (fclose(stdin) != 0) {
      fprintf(stderr, "failed to close stdin\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    for (int i = 0; i < argc - 1; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "failed to open file %s\n", argv[i]);
        exit(EXIT_FAILURE);
      }
      Mysort(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "failed to close file %s\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
