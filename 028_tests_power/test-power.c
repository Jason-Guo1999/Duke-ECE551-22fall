#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned, unsigned);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("Umm, something wrong with the function :(, input was base:%u, exponent:%u",
           x,
           y);
    exit(EXIT_FAILURE);
  }
}
int main() {
  run_check(1, 1, 1);
  run_check(1, 0, 1);
  run_check(0, 1, 0);
  run_check(0, 0, 1);
  run_check(2, 0, 1);
  run_check(2, 2, 4);
  run_check(3, 3, 27);
  run_check(12, 1, 12);
  run_check(power(2, 32) - 1, 1, power(2, 32) - 1);
  return EXIT_SUCCESS;
}
