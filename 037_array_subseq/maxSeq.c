#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0 || n == 1) {
    return n;
  }
  size_t ans = 1;
  int * ptr1 = array;
  int * ptr2 = array + 1;
  while (ptr2 < array + n) {
    if (*ptr2 > *(ptr2 - 1)) {
      ptr2++;
    }
    else {
      ans = (ptr2 - ptr1) > ans ? (ptr2 - ptr1) : ans;
      ptr1 = ptr2;
      ptr2++;
    }
  }
  ans = (ptr2 - ptr1) > ans ? (ptr2 - ptr1) : ans;
  return ans;
}
