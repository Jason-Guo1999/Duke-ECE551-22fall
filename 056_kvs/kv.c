#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void readPair(kvpair_t * pair, char * line) {
  char * ptr;
  char * ptr1;
  ptr = strchr(line, '=');
  pair->key = line;
  pair->value = ptr + 1;
  ptr1 = strchr(line, '\n');
  *ptr = '\0';
  *ptr1 = '\0';
}
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");

  kvarray_t * myKv = malloc(sizeof(*myKv));
  // Initialize //
  myKv->num = 0;
  myKv->pairArray = malloc(sizeof(*myKv->pairArray));
  // read line by line //
  char * line = NULL;
  size_t l = 0;
  size_t len = 0;
  while (getline(&line, &l, f) >= 0) {
    myKv->num++;
    myKv->pairArray = realloc(myKv->pairArray, myKv->num * sizeof(*myKv->pairArray));
    kvpair_t * pair = malloc(sizeof(*pair));
    readPair(pair, line);
    myKv->pairArray[len] = pair;
    len++;
    line = NULL;
  }
  fclose(f);
  free(line);
  return myKv;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < (pairs->num); i++) {
    free(pairs->pairArray[i]->key);
    free(pairs->pairArray[i]);
  }
  free(pairs->pairArray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->num; i++) {
    printf("key = '%s' value = '%s'\n",
           pairs->pairArray[i]->key,
           pairs->pairArray[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->num; i++) {
    if (strcmp(pairs->pairArray[i]->key, key) == 0) {
      return pairs->pairArray[i]->value;
    }
  }
  return NULL;
}
