#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void callError(char * message) {
  // common function to report error //
  perror(message);
  exit(EXIT_FAILURE);
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
//char * findword(char * target, int flag) {

//}

void replaceTemplate(file * temp, int flag) {
  // replace _XXX_ to some contents //
  // flag==0 : default, replace by "cat"

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
      //char * target = strndup(ptr1 + 1, targetSz);
      char * part1 = strndup(line, p1);
      char * part2 = strndup(ptr2 + 1, p2);

      //Todo:
      //char * word = findWord(target, flag);
      char * word = "cat";
      size_t w = strlen(word);
      // string cat: result = part1+word+part2
      part1 = realloc(part1, (p1 + p2 + w + 1) * sizeof(*part1));
      part1 = strcat(part1, word);
      char * result = strcat(part1, part2);
      free(temp->lines[i]);
      //temp->lines[i] = malloc((p1 + p2 + w + 1) * sizeof(*temp->lines[i]));
      temp->lines[i] = strndup(result, p1 + p2 + w + 1);
      free(part1);
      free(part2);
    }
  }
  return;
}
