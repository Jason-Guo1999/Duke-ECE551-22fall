#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 3 || argc > 4) {
    callError("Invalid command line");
  }
  FILE * f1;
  FILE * f2;
  int flag = 0;
  // if we don't have '-n' command
  if (argc == 3) {
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    if (f1 == NULL || f2 == NULL) {
      callError("Failed to open file!");
    }
    flag = 1;
  }
  // we have '-n' command
  else {
    if (strcmp(argv[1], "-n") != 0) {
      callError("Unknown command!");
    }
    f1 = fopen(argv[2], "r");
    f2 = fopen(argv[3], "r");
    if (f1 == NULL || f2 == NULL) {
      callError("Failed to open file!");
    }
    flag = 2;
  }
  // get template
  file * temp = getTemplate(f2);
  // get category
  catarray_t * catArray = getCatArray(f1);
  // replace template
  replaceTemplate(temp, catArray, flag);
  // print result
  helperPrintStep1(temp);
  // free memory
  helperFreeStep1(temp);
  helperFreeStep2(catArray);
  // close file
  int c1 = fclose(f1);
  int c2 = fclose(f2);
  if (c1 != 0) {
    callError("Can't close file 1");
  }
  if (c2 != 0) {
    callError("Can't close file 2");
  }
  return EXIT_SUCCESS;
}
