#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int left = low;
  int right = high - 1;
  if (left >= right) {
    return left;
  }
  while (left < right) {
    int mid = left + ((right - left) >> 1) + 1;
    int temp = f->invoke(mid);
    if (temp <= 0) {
      left = mid;
    }
    else {
      high = mid - 1;
    }
  }
  return left;
}
