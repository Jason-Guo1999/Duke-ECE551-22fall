#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
  if (a == 0) {
    return b;
  }
  else if (b == 0) {
    return a;
  }
  else if (a == b) {
    return a;
  }
  else if (a > b) {
    return gcd(a % b, b);
  }
  else {
    gcd(a, b % a);
  }
  return 0;
}

int main() {
  int a[7];
  int * ptr = a;
  *ptr = gcd(0, 0);
  *(ptr + 1) = gcd(0, 1);
  a[2] = gcd(1, 0);
  a[3] = gcd(2, 5);
  a[4] = gcd(3, 6);
  a[5] = gcd(100, 200);
  a[6] = gcd(101, 37);
  for (int i = 0; i < 7; i++) {
    printf("%d", a[i]);
  }
  return EXIT_SUCCESS;
}
