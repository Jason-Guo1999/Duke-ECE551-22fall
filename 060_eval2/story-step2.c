#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // input command check
  if (argc != 2) {
    callError("Invalid command line!");
  }
  // open file
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    callError("Can't open file!");
  }
  // get category
  catarray_t * catArray = getCatArray(f);
  // close file
  int c = fclose(f);
  if (c != 0) {
    callError("Can't close file!");
  }
  // print result
  printWords(catArray);
  // free memory
  helperFreeStep2(catArray);
  return EXIT_SUCCESS;
}
