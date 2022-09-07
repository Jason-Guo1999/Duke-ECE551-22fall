#include <stdio.h>
#include <stdlib.h>

extern size_t maxSeq(int * array, size_t n);

void runCheck(int * array, size_t n, size_t expected) {
  if (expected != maxSeq(array, n)) {
    exit(EXIT_FAILURE);
  }
  return;
}

int main() {
  int array1[] = {0};
  int array2[] = {1, 1};
  int array3[] = {-2147483648, 2147483647};
  int array4[] = {1, 0, 1, 0, 1};
  int array5[] = {1, 2, 3, 4, 5};
  runCheck(NULL, 0, 0);
  runCheck(array1, 1, 1);
  runCheck(array2, 2, 1);
  runCheck(array3, 2, 2);
  runCheck(array4, 5, 2);
  runCheck(array5, 5, 5);
  return EXIT_SUCCESS;
}
