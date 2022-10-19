#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

file * getTemplate(FILE * f) {
  // helper function to get template from given input file
  char * line = NULL;
  size_t sz = 0;
  file * temp = malloc(sizeof(*temp));
  temp->lines = malloc(sizeof(*temp->lines));
  temp->nums = 0;
  if (temp == NULL) {
    callError("Failed to malloc!");
  }
  while (getline(&line, &sz, f) >= 0) {
    temp->lines = realloc(temp->lines, (temp->nums + 1) * sizeof(*temp->lines));
    if (temp->lines == NULL) {
      callError("Failed to realloc!");
    }
    temp->lines[temp->nums] = line;
    temp->nums++;
    line = NULL;
  }
  free(line);
  return temp;
}
void helperPrint(file * temp) {
  // print each line
  for (size_t i = 0; i < temp->nums; i++) {
    printf("%s", temp->lines[i]);
  }
  return;
}
void helperFree(file * temp) {
  // helper function to free template
  for (size_t i = 0; i < temp->nums; i++) {
    free(temp->lines[i]);
  }
  free(temp->lines);
  free(temp);
  return;
}

int main(int argc, char ** argv) {
  // input check
  if (argc != 2) {
    callError("Invalid command line!");
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    callError("Invalid input file!");
  }
  file * template = getTemplate(f);
  int close = fclose(f);
  if (close != 0) {
    callError("Can't close file!");
  }
  // replace _XXX_
  replaceTemplate(template, 0);
  // print result
  helperPrint(template);
  // free memory
  helperFree(template);
  return EXIT_SUCCESS;
}
