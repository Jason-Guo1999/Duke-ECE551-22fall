#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->size = 0;
  ans->unknown = 0;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
  }
  else {
    int find = 0;
    for (int i = 0; i < c->size; i++) {
      if (strcmp(c->arr[i]->key, name) == 0) {
        c->arr[i]->count++;
        find = 1;
      }
    }
    // name appears for the first time //
    if (find == 0) {
      c->size++;
      c->arr = realloc(c->arr, c->size * sizeof(*c->arr));
      one_count_t * new = malloc(sizeof(*new));
      c->arr[c->size - 1] = new;
      c->arr[c->size - 1]->key = name;
      c->arr[c->size - 1]->count = 1;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s:%d\n", c->arr[i]->key, c->arr[i]->count);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown>:%d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->arr[i]);
  }
  free(c->arr);
  free(c);
}
