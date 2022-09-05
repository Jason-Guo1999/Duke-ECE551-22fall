#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("Umm, something wrong with the function :(, input was base:%d, exponent:%d",
           x,
           y);
    exit(EXIT_FAILURE);
  }
}
int main() {
  run_check(0, 1, 0);
  run_check(0, 0, 1);
  run_check(2, 0, 1);
  run_check(3, 3, 27);
  run_check(12, 1, 12);
  return EXIT_SUCCESS;
}
