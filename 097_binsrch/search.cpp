#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int mid = low + ((high - low) >> 1) + 1;
    int temp = f->invoke(mid);
    if (temp <= 0) {
      low = mid;
    }
    else {
      high = mid;
    }
  }
  return low;
}
