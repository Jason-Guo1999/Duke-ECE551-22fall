#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 2) {
    callError("Invalid command line!");
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    callError("Can't open file!");
  }
  catarray_t * catArray = getCatArray(f);
  int c = fclose(f);
  if (c != 0) {
    callError("Can't close file!");
  }
  printWords(catArray);
  helperFreeStep2(catArray);
  return EXIT_SUCCESS;
}
