#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned base, unsigned component) {
  if (component == 0) {
    return 1;
  }
  else if (base == 0) {
    return 0;
  }
  else {
    unsigned temp = power(base, component / 2);
    if (component % 2 == 0) {
      return temp * temp;
    }
    else {
      return temp * temp * base;
    }
  }
  return 0;
}
