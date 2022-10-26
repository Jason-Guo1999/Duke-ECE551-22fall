#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  // input command check
  if (argc != 2) {
    callError("Invalid command line!");
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    callError("Invalid input file!");
  }
  // get template
  file * template = getTemplate(f);
  // close file
  int close = fclose(f);
  if (close != 0) {
    callError("Can't close file!");
  }
  // replace _XXX_
  replaceTemplate(template, NULL, 0);
  // print result
  helperPrintStep1(template);
  // free memory
  helperFreeStep1(template);
  return EXIT_SUCCESS;
}
