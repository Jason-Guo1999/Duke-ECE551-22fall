#include <math.h>

#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class sinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class poslFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg + 1; }
};

class neglFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -arg - 1; }
};

class negFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

class posFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 1; }
};

class squareFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg * arg + 1; }
};

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int maxInvo;
  if (high > low) {
    maxInvo = log(high - low) / log(2) + 1;
  }
  else {
    maxInvo = 1;
  }
  CountedIntFn * myC = new CountedIntFn(maxInvo, f, mesg);
  if (binarySearchForZero(myC, low, high) != expected_ans) {
    //std::cerr << "wrong answer!" << mesg << std::endl;
    fprintf(stderr, "Wrong output answer in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}
int main() {
  sinFunction sinf;
  negFunction nf;
  posFunction pf;
  neglFunction nlf;
  poslFunction plf;
  squareFunction sf;
  check(&sinf, 0, 150000, 52359, "1");

  check(&nf, -100, 100, 99, "2");
  check(&nf, 100, 1000, 999, "3");
  check(&nf, -1000, -100, -101, "4");

  check(&pf, -100, 100, -100, "5");
  check(&pf, 100, 1000, 100, "6");
  check(&pf, -1000, -100, -1000, "7");

  check(&plf, -100, 100, -1, "8");
  check(&plf, 100, 1000, 100, "9");
  check(&plf, -1000, -100, -101, "10");

  check(&nlf, -100, 100, 99, "11");
  check(&nlf, 100, 1000, 999, "12");
  check(&nlf, -1000, -100, -1000, "13");

  check(&sf, -100, 100, -100, "14");
  check(&sf, 100, 1000, 100, "15");
  check(&sf, -1000, -100, -1000, "16");
}
