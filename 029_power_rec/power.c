#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (x == 0) {
    return 0;
  }
  else {
    unsigned temp = power(x, y / 2);
    if (y % 2 == 0) {
      return temp * temp;
    }
    else {
      return temp * temp * x;
    }
  }
  return 0;
}
