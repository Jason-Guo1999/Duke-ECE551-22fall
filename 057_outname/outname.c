#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  // name+".counts+'\0'"
  unsigned length = strlen(inputName) + 8;
  char * ans = malloc(length * sizeof(*ans));
  ans = strcpy(ans, inputName);
  ans = strcat(ans, ".counts");
  return ans;
}
