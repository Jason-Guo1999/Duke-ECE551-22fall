#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"
void validLine(char * line) {
  // helper function to validate line
  char * ptr1 = strchr(line, ':');
  if (ptr1 == NULL) {
    callError("Invalid line, miss ':'!");
  }
  else if (ptr1 - line == 0) {
    callError("Invalid line, empty name!");
  }
  ptr1++;
  char * ptr2 = strchr(ptr1, '\n');
  if (ptr2 != NULL) {
    if (ptr2 - ptr1 == 0) {
      callError("Invalid line, empty word!");
    }
  }
  else {
    if (strlen(line) - (ptr1 - line - 1) == 1) {
      callError("Invalid line, empty word!");
    }
  }
  return;
}

catarray_t * getCatArray(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  catarray_t * catArray = malloc(sizeof(*catArray));
  catArray->arr = malloc(sizeof(*catArray->arr));
  catArray->n = 0;
  while (getline(&line, &sz, f) >= 0) {
    validLine(line);
    char * ptr1 = strchr(line, ':');
    char * tempName = strndup(line, ptr1 - line);
    ptr1++;
    char * ptr2 = strchr(line, '\n');
    size_t szWord = 0;
    if (ptr2 != NULL) {
      szWord = ptr2 - ptr1;
    }
    else {
      szWord = strlen(line) - (ptr1 - line - 1);
    }
    char * tempWord = strndup(ptr1, szWord);
    // only if we can't find a NAME, realloc catArray->arr
    category_t * target = findName(catArray, tempName);
    if (target == NULL) {
      // we find a new name! allocate space for it!
      // initialize a new category
      category_t * newCat = malloc(sizeof(*newCat));
      newCat->n_words = 1;
      newCat->name = tempName;
      newCat->words = malloc(sizeof(*newCat->words));
      newCat->words[0] = tempWord;
      // add category to catArray
      catArray->arr = realloc(catArray->arr, (catArray->n + 1) * sizeof(*catArray->arr));
      if (catArray->arr == NULL) {
        callError("Failed to allocate!");
      }
      catArray->arr[catArray->n] = *newCat;
      free(newCat);
      catArray->n++;
    }
    else {
      // we could find an exist name, just add new category to it
      free(tempName);
      target->words =
          realloc(target->words, (target->n_words + 1) * sizeof(*target->words));
      target->words[target->n_words] = tempWord;
      target->n_words++;
    }
    //line = NULL;
  }
  free(line);
  return catArray;
}

void helperFree(catarray_t * catArray) {
  // helper function to free memory
  for (size_t i = 0; i < catArray->n; i++) {
    for (size_t j = 0; j < catArray->arr[i].n_words; j++) {
      free(catArray->arr[i].words[j]);
    }
    free(catArray->arr[i].name);
    free(catArray->arr[i].words);
  }
  free(catArray->arr);
  free(catArray);
  return;
}
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
  helperFree(catArray);
  return EXIT_SUCCESS;
}
