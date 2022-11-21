#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f;
  f.open(fname);
  char ch;
  uint64_t * fre = new uint64_t[257]();
  // eof == 1
  fre[256] = 1;
  while (f.get(ch)) {
    fre[(size_t)ch]++;
  }
  f.close();
  return fre;
}
