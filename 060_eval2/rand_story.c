#include "rand_story.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void callError(char * message) {
  // common function to report error //
  perror(message);
  exit(EXIT_FAILURE);
}

void validLineStep2(char * line) {
  // helper function to validate line
  char * ptr1 = strchr(line, ':');
  //if (ptr1 == NULL) {
  // can't find ':'
  //callError("Invalid line, miss ':'!");
  //}
  if (ptr1 - line == 0) {
    // can't find name
    callError("Invalid line, empty name!");
  }
  ptr1++;
  char * ptr2 = strchr(ptr1, '\n');
  if (ptr2 != NULL) {
    if (ptr2 - ptr1 == 0) {
      // can't find word
      callError("Invalid line, empty word!");
    }
  }
  else {
    if (strlen(line) - (ptr1 - line - 1) == 1) {
      // can't find word
      callError("Invalid line, empty word!");
    }
  }
  return;
}

catarray_t * getCatArray(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  catarray_t * catArray = malloc(sizeof(*catArray));
  if (catArray == NULL) {
    callError("Failed to allocate!");
  }
  catArray->arr = malloc(sizeof(*catArray->arr));
  if (catArray->arr == NULL) {
    callError("Failed to allocate!");
  }
  catArray->n = 0;
  // read line
  while (getline(&line, &sz, f) >= 0) {
    // call helperfunction to validate line
    validLineStep2(line);
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
      if (newCat->words == NULL) {
        callError("Failed to allocate!");
      }
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
      if (target->words == NULL) {
        callError("Failed to reallocate");
      }
      target->words[target->n_words] = tempWord;
      target->n_words++;
    }
  }
  free(line);
  return catArray;
}
void helperFreeStep2(catarray_t * catArray) {
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

category_t * findName(catarray_t * catArray, char * tempName) {
  // helper function to find if tempName is already existing
  category_t * ans = NULL;
  if (catArray->n == 0) {
    // we don't have any catgory yet!
    return ans;
  }
  for (size_t i = 0; i < catArray->n; i++) {
    if (strcmp(tempName, catArray->arr[i].name) == 0) {
      ans = &catArray->arr[i];
      break;
    }
  }
  return ans;
}

void replaceTemplate(file * temp, catarray_t * catArray, int flag) {
  // replace _XXX_ to some contents //
  // flag==0 : default, replace by "cat"

  // create a "previously used" category
  category_t * previous = malloc(sizeof(*previous));
  previous->name = NULL;
  previous->n_words = 0;
  previous->words = malloc(sizeof(*previous->words));
  for (size_t i = 0; i < temp->nums; i++) {
    // for each line, replace _XXX_
    // algo: line -> part1 + _XXX_ + part2
    // replace: line -> part1 + word + part2

    while (1) {
      char * ptr1 = strchr(temp->lines[i], '_');
      char * line = temp->lines[i];
      if (ptr1 == NULL) {
        // if we can't find '_', jump out the loop
        break;
      }
      char * ptr2 = strchr(ptr1 + 1, '_');
      if (ptr1 != NULL && ptr2 == NULL) {
        callError("Invalid input, disclosure of '_'!");
      }
      // duplicate parts of the string
      size_t targetSz = ptr2 - ptr1 - 1;
      size_t p1 = ptr1 - line;
      size_t p2 = strlen(line) - p1 - targetSz - 2;
      char * target = strndup(ptr1 + 1, targetSz);
      char * part1 = strndup(line, p1);
      char * part2 = strndup(ptr2 + 1, p2);

      const char * word = findWord(target, catArray, previous, flag);
      //
      size_t w = strlen(word);
      // string cat: result = part1+word+part2
      part1 = realloc(part1, (p1 + p2 + w + 1) * sizeof(*part1));
      part1 = strcat(part1, word);
      char * result = strcat(part1, part2);
      free(temp->lines[i]);
      temp->lines[i] = strndup(result, p1 + p2 + w);
      free(part1);
      free(part2);
      free(target);
    }
  }
  // free previous
  for (size_t i = 0; i < previous->n_words; i++) {
    free(previous->words[i]);
  }
  free(previous->words);
  free(previous);
  return;
}
const char * findWord(char * target,
                      catarray_t * catArray,
                      category_t * previous,
                      int flag) {
  if (flag == 0) {
    return "cat";
  }
  const char * ans = NULL;
  // first: find target in catArray, if compatible, return random word, add it to previous word
  for (size_t i = 0; i < catArray->n; i++) {
    if (strcmp(target, catArray->arr[i].name) == 0) {
      ans = chooseWord(target, catArray);
      addToPrevious(ans, previous);
      return ans;
    }
  }
  // second: can't find in catArray, test if it is valid integer
  char * sentinel = target;
  while (*target != '\0') {
    if (*target < '0' || *target > '9') {
      callError("Invalid category! invalid integer");
    }
    target++;
  }
  target = sentinel;
  size_t tempInt = atoll(target);
  if (tempInt > INT_MAX) {
    callError("Invalid category! integer overflow");
  }
  if (tempInt < 0) {
    callError("Invalid category! negative");
  }
  // third : valid integer, find in previous category
  if (tempInt > previous->n_words || tempInt == 0) {
    callError("Invalid category! previous overflow");
  }
  ans = previous->words[previous->n_words - tempInt];
  // add ans to previous used string
  addToPrevious(ans, previous);
  return ans;
}

void addToPrevious(const char * target, category_t * previous) {
  previous->words =
      realloc(previous->words, (previous->n_words + 1) * sizeof(*previous->words));
  if (previous == NULL) {
    callError("Failed to realloc");
  }
  previous->words[previous->n_words] = strndup(target, strlen(target));
  previous->n_words++;
  return;
}

void helperPrintStep1(file * temp) {
  // print each line
  for (size_t i = 0; i < temp->nums; i++) {
    printf("%s", temp->lines[i]);
  }
  return;
}

void helperFreeStep1(file * temp) {
  // helper function to free template
  for (size_t i = 0; i < temp->nums; i++) {
    free(temp->lines[i]);
  }
  free(temp->lines);
  free(temp);
  return;
}
