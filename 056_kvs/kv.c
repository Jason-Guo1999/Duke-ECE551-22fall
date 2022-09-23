#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("no such file");
    return NULL;
  }

  kvarray_t * myKv = malloc(sizeof(*myKv));
  // Initialize //
  myKv->num = 0;
  myKv->pairArray = NULL;
  // read line by line //
  char * line = NULL;
  size_t l = 0;
  size_t len = 0;
  while (getline(&line, &l, f) >= 0) {
    char * ptr;
    char * ptr2;
    myKv->num++;
    myKv->pairArray = realloc(myKv->pairArray, myKv->num * sizeof(*myKv->pairArray));
    kvpair_t * pair = malloc(sizeof(*pair));
    ptr = strchr(line, '=');
    pair->key = line;
    if (ptr != NULL) {
      *ptr = '\0';
    }
    pair->value = ptr + 1;
    ptr2 = strchr(pair->value, '\n');
    if (ptr2 != NULL) {
      *ptr2 = '\0';
    }
    // else {
    //fprintf(stderr, "invalid input(ptr2)\n");
    //exit(EXIT_FAILURE);
    //}
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
  for (int i = 0; i < pairs->num; i++) {
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
    if (strcmp(key, pairs->pairArray[i]->key)) {
      return pairs->pairArray[i]->value;
    }
  }
  return NULL;
}
