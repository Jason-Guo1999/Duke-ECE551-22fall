#ifndef _HELPERFUNCTIONHPP_
#define _HELPERFUNCTIONHPP_

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "myException.hpp"

bool findFile(const char * path) {
  // helper function to test the path of file
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
  // check whether number is valid
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
  // decide line mode (4 modes) according to the first special letter we meet
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
      else if (line[i] == '$') {
        // mode 3, item change
        return 3;
      }
      else if (line[i] == '[') {
        // mode 4, special choices
        return 4;
      }
    }
  }
  return 0;
}

void printWinPath(std::vector<std::vector<std::string> > & winPath) {
  // helper function for step3, print the answer
  if (winPath.size() == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
    return;
  }
  for (size_t i = 0; i < winPath.size(); i++) {
    for (size_t j = 0; j < winPath[i].size(); j++) {
      if (winPath[i][j] != winPath[i].back()) {
        std::cout << winPath[i][j] << ",";
      }
      else {
        std::cout << winPath[i][j] << std::endl;
      }
    }
  }
}

std::string toString(size_t target) {
  std::string ans;
  if (target == 0) {
    ans.push_back('0');
  }
  while (target != 0) {
    ans.push_back('0' + (target % 10));
    target = target / 10;
  }
  std::reverse(ans.begin(), ans.end());
  return ans;
}
#endif
