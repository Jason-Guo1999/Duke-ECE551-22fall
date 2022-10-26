#include "rand_story.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void callError(char * message) {
  // common function to report and descript error //
  perror(message);
  exit(EXIT_FAILURE);
}

/* This function is used to validate each line in template */
void validLineStep2(char * line) {
  // helper function to validate line
  char * ptr1 = strchr(line, ':');
  if (ptr1 == NULL) {
    // can't find ':'
    callError("Invalid line, miss ':'!");
  }
  else if (ptr1 - line == 0) {
    // can't find name
    callError("Invalid line, empty name!");
  }
  ptr1++;
  char * ptr2 = strchr(ptr1, '\n');
  // deal with last line in file (without '\n')
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

/* This function is used to parse input words.txt to get category*/
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
  char * tempName = NULL;
  char * tempWord = NULL;
  // read line
  while (getline(&line, &sz, f) >= 0) {
    // call helperfunction to validate line
    validLineStep2(line);
    char * ptr1 = strchr(line, ':');
    tempName = strndup(line, ptr1 - line);
    ptr1++;
    char * ptr2 = strchr(line, '\n');
    // check the last line (without '\n')
    if (ptr2 != NULL) {
      *ptr2 = '\0';
      tempWord = strdup(ptr1);
    }
    else {
      tempWord = strdup(ptr1);
    }
    // only if we can't find a NAME, realloc catArray->arr
    category_t * target = findName(catArray, tempName);
    if (target == NULL) {
      // we find a new name! allocate space for it!
      // initialize a new category
      category_t newCat;
      newCat.n_words = 1;
      newCat.name = strdup(tempName);
      newCat.words = malloc(sizeof(*newCat.words));
      if (newCat.words == NULL) {
        callError("Failed to allocate!");
      }
      newCat.words[0] = strdup(tempWord);
      // add category to catArray
      catArray->arr = realloc(catArray->arr, (catArray->n + 1) * sizeof(*catArray->arr));
      if (catArray->arr == NULL) {
        callError("Failed to allocate!");
      }
      catArray->arr[catArray->n] = newCat;
      catArray->n++;
    }
    else {
      // we can find an exist name, just add new category to it

      target->words =
          realloc(target->words, (target->n_words + 1) * sizeof(*target->words));
      if (target->words == NULL) {
        callError("Failed to reallocate");
      }
      target->words[target->n_words] = strdup(tempWord);
      target->n_words++;
    }
    free(tempName);
    free(tempWord);
  }
  free(line);
  return catArray;
}

/* This function is used to free memory allocated in step2 (get category) */
void helperFreeStep2(catarray_t * catArray) {
  // helper function to free memory of catgory
  for (size_t i = 0; i < catArray->n; i++) {
    if (catArray->arr[i].n_words != 0) {
      for (size_t j = 0; j < catArray->arr[i].n_words; j++) {
        free(catArray->arr[i].words[j]);
      }
    }
    free(catArray->arr[i].words);
    free(catArray->arr[i].name);
  }
  free(catArray->arr);
  free(catArray);
  return;
}

/* This function is used to get template from input story.txt */
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
  // parse each line
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

/* This function is to find proper name to replacec the _XXX_ */
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

/* This function is used to replace _XXX_ with word we find */
void replaceTemplate(file * temp, catarray_t * catArray, int mode) {
  // replace _XXX_ to some contents //
  // flag==0 : default, replace by "cat"
  // flag==1 : find word in correlating category
  // flag==2 : delete word after use
  // create a "previously used" category
  category_t previous;
  previous.name = "previous";
  previous.n_words = 0;
  previous.words = NULL;
  for (size_t i = 0; i < temp->nums; i++) {
    // for each line, replace _XXX_
    // algo: line -> part1 + _XXX_ + part2
    // replace: line -> part1 + word + part2
    // concatenate
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
      size_t p1Sz = ptr1 - line;
      size_t p2Sz = strlen(line) - p1Sz - targetSz - 2;

      char * target = strndup(ptr1 + 1, targetSz);
      char * part1 = strndup(line, p1Sz);
      char * part2 = strndup(ptr2 + 1, p2Sz);

      char * word = findWord(target, catArray, &previous, mode);
      size_t w = strlen(word);
      // string cat: result = part1+word+part2
      part1 = realloc(part1, (p1Sz + p2Sz + w + 2) * sizeof(*part1));
      part1 = strcat(part1, word);
      char * result = strcat(part1, part2);
      free(temp->lines[i]);
      temp->lines[i] = strdup(result);
      // free
      free(part1);
      free(part2);
      free(target);
      free(word);
    }
  }
  // free previous
  for (size_t i = 0; i < previous.n_words; i++) {
    if (previous.words[i] != NULL) {
      free(previous.words[i]);
    }
  }
  free(previous.words);
  return;
}
/* This function is used to delete previously used words (step4, with -n command) */
category_t deleteWord(const char * target, category_t cate) {
  // deep copy, lengh--
  category_t cat;
  cat.name = strdup(cate.name);
  if (cate.n_words == 1) {
    cat.n_words = 0;
    cat.words = malloc(sizeof(*cat.words));
    return cat;
  }
  cat.n_words = cate.n_words - 1;
  cat.words = malloc((cat.n_words) * sizeof(*cat.words));
  size_t ptr = 0;
  // copy other contents except the used one
  for (size_t j = 0; j < cate.n_words; j++) {
    if (strcmp(cate.words[j], target) != 0) {
      cat.words[ptr] = strdup(cate.words[j]);
      ptr++;
    }
  }
  return cat;
}

/* This function is used to find proper words according to different working modes */
char * findWord(char * target, catarray_t * catArray, category_t * previous, int mode) {
  char * ans = NULL;
  if (mode == 0) {
    const char * tempAns = chooseWord(target, NULL);
    ans = strdup(tempAns);
    return ans;
  }

  // first: find target in catArray, if strcmp==0, return random word, add it to previous word
  for (size_t i = 0; i < catArray->n; i++) {
    if (strcmp(target, catArray->arr[i].name) == 0) {
      // if the category is already used up, error
      if (catArray->arr[i].n_words == 0) {
        callError("Insufficient word to use!");
      }
      const char * tempAns = chooseWord(target, catArray);
      ans = strdup(tempAns);
      addToPrevious(ans, previous);
      // if mode==2 (can't reuse)
      // 1.delete this word from current category
      // 2.shorten the length, if length==0, delete category
      if (mode == 2) {
        category_t t = deleteWord(ans, catArray->arr[i]);
        // delete
        for (size_t k = 0; k < catArray->arr[i].n_words; k++) {
          free(catArray->arr[i].words[k]);
        }
        free(catArray->arr[i].name);
        free(catArray->arr[i].words);
        catArray->arr[i] = t;
      }
      return ans;
    }
  }
  // second: can't find in catArray, test if it is valid integer
  // 01 -> invalid; -1->invalid; 1asff->invalid
  char * sentinel = target;
  if (*sentinel == '0') {
    callError("Invalid category! integer start with 0");
  }
  while (*target != '\0') {
    if (*target < '0' || *target > '9') {
      callError("Invalid category! invalid integer");
    }
    target++;
  }
  target = sentinel;
  int tempInt = atoi(target);
  if (tempInt > INT_MAX) {
    callError("Invalid category! integer overflow");
  }
  if (tempInt < 0) {
    callError("Invalid category! negative");
  }
  // third : valid integer, find in previous category
  if ((size_t)tempInt > previous->n_words || tempInt == 0) {
    callError("Invalid category! previous overflow");
  }
  ans = strdup(previous->words[previous->n_words - tempInt]);
  // add ans to previous used string
  addToPrevious(ans, previous);
  return ans;
}

/* This function is used to add the word into previously used array */
void addToPrevious(char * target, category_t * previous) {
  // helper function to add word into previously used array
  previous->words =
      realloc(previous->words, (previous->n_words + 1) * sizeof(*previous->words));
  if (previous == NULL) {
    callError("Failed to realloc");
  }
  previous->words[previous->n_words] = strndup(target, strlen(target));
  previous->n_words++;
  return;
}

/* This function helps us print the story */
void helperPrintStep1(file * temp) {
  // print each line
  for (size_t i = 0; i < temp->nums; i++) {
    printf("%s", temp->lines[i]);
  }
  return;
}
/* This function helps us free the template */
void helperFreeStep1(file * temp) {
  // helper function to free template
  for (size_t i = 0; i < temp->nums; i++) {
    free(temp->lines[i]);
  }
  free(temp->lines);
  free(temp);
  return;
}
