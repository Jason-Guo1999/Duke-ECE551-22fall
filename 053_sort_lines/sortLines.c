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

void mySort(FILE * f) {
  char ** lines = malloc(sizeof(*lines));
  if (lines == NULL) {
    fprintf(stderr, "No memory to allocate!");
    exit(EXIT_FAILURE);
  }
  size_t lsize = 0;
  size_t numOflines = 0;
  char * l = 0;
  while (getline(&l, &lsize, f) >= 0) {
    lines = realloc(lines, (numOflines + 1) * sizeof(*lines));
    if (lines == NULL) {
      perror("No memory to allocate!");
      exit(EXIT_FAILURE);
    }
    lines[numOflines] = l;
    numOflines++;
    l = 0;
  }
  sortData(lines, numOflines);
  for (size_t i = 0; i < numOflines; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
  free(l);
  return;
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      fprintf(stderr, "Can not open file!");
      exit(EXIT_FAILURE);
    }
    mySort(f);
    if (fclose(stdin) != 0) {
      fprintf(stderr, "failed to close stdin\n");
      exit(EXIT_FAILURE);
    }
  }
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Can not open file");
        exit(EXIT_FAILURE);
      }
      mySort(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "failed to close file %s\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
