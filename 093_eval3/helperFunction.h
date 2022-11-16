#ifndef _HELPERFUNCTIONH_
#define _HELPERFUNCTIONH_

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "myException.h"

bool findFile(const char * path) {
  std::ifstream file;
  file.open(path);
  if (!file) {
    return false;
  }
  else {
    file.close();
  }
  return true;
}

bool validNumber(std::string target) {
  bool visitDigit = false;
  for (size_t i = 0; i < target.size(); i++) {
    if (target[i] == ' ' && !visitDigit) {
      continue;
    }
    if (target[i] == ' ' && visitDigit) {
      return false;
    }
    if (target[i] < '0' || target[i] > '9') {
      return false;
    }
    else {
      visitDigit = true;
    }
  }
  return true;
}

int decideLineMode(std::string line) {
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == ' ') {
      continue;
    }
    if (line[i] >= '0' && line[i] <= '9') {
      continue;
    }
    else {
      if (line[i] == '@') {
        // mode 1, content
        return 1;
      }
      else if (line[i] == ':') {
        // mode 2, choices
        return 2;
      }
    }
  }
  return 0;
}
#endif
