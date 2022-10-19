#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 3) {
    callError("Invalid command line!");
  }
  // open file1 (step1)
  FILE * f1 = fopen(argv[1], "r");
  if (f1 == NULL) {
    callError("Can't open file 1!");
  }
  // open file2 (step2)
  FILE * f2 = fopen(argv[2], "r");
  if (f2 == NULL) {
    callError("Can't open file 2!");
  }

  // get template first: use step1
  file * temp = getTemplate(f1);
  // get category : use step2
  catarray_t * catArray = getCatArray(f2);
  // replace template, mode = 1
  replaceTemplate(temp, catArray, 1);
  // print result
  helperPrintStep1(temp);
  // free memory
  helperFreeStep1(temp);
  helperFreeStep2(catArray);
  int c1 = fclose(f1);
  if (c1 != 0) {
    callError("Can't close file 1!");
  }

  int c2 = fclose(f2);
  if (c2 != 0) {
    callError("Can't close file 2!");
  }

  return EXIT_SUCCESS;
}
