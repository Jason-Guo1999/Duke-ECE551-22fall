#ifndef _PAGEH_
#define _PAGEH_

#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "helperFunction.h"

class Page {
 public:
  // indicate if we get win or lose state
  bool win;
  bool lose;
  // store choices
  std::unordered_map<std::string, size_t> choicesMap;
  std::vector<std::string> choices;
  // store contents
  std::vector<std::string> contents;

  Page() : win(false), lose(false) {}
  // initialize thorugh a given page.txt
  Page(std::string s, std::string directory) {
    size_t findAt = s.find('@');
    /*
    // validate pageNum and file name
    size_t pageNum = std::strtoll(s.substr(0, findAt).c_str(), NULL, 10);
    
    size_t findDot = s.find('.');
    size_t findE = s.find('e');
    size_t fileNameNumber =
        std::strtoll(s.substr(findE + 1, findDot - findE - 1).c_str(), NULL, 10);
    try {
      if (pageNum != fileNameNumber) {
        throw myException("Uncompatible pageNum and filename!");
      }
    }
    catch (myException & re) {
      std::cerr << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    */
    std::string tempFilePath = directory + "/" + s.substr(findAt + 3);
    const char * filePath = tempFilePath.c_str();
    std::ifstream file;
    if (!findFile(filePath)) {
      std::cerr << "Can't open given story file!" << std::endl;
      exit(EXIT_FAILURE);
    }
    file.open(filePath);

    std::string line;
    while (getline(file, line)) {
      // read content
      contents.push_back(line);

      // read a normal page
      if (s[findAt + 1] == 'N') {
        win = false;
        lose = false;
      }
      // read a win page
      else if (s[findAt + 1] == 'W') {
        win = true;
        lose = false;
      }
      //read a lose page
      else if (s[findAt + 1] == 'L') {
        win = false;
        lose = true;
      }
      else {
        std::cout << "Invalid State name" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    choices = std::vector<std::string>();
    choicesMap = std::unordered_map<std::string, size_t>();
  }

  // print page according to different states
  void printPage() {
    // print contents firstly
    for (size_t i = 0; i < contents.size(); i++) {
      std::cout << contents[i] << std::endl;
    }
    // if we win or lose, print result
    std::cout << std::endl;
    if (win || lose) {
      if (win) {
        std::cout << "Congratulations! You have won. Hooray!" << std::endl;
      }
      else {
        std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
      }
    }
    // else, print choices
    else {
      std::cout << "What would you like to do?" << std::endl;
      std::cout << std::endl;
      for (size_t i = 1; i < choices.size() + 1; i++) {
        std::cout << i << "." << choices[i - 1] << std::endl;
      }
    }
  }
  // read choice from given string
  void getChoices(std::string target) {
    // win or lose page can't have any choices
    try {
      if (win || lose) {
        throw myException("Win or Lose page can't have choices!");
      }
    }
    catch (myException & re) {
      std::cout << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    size_t findColon = target.find(':');
    size_t targetPage = std::strtoull(target.substr(0, findColon).c_str(), NULL, 10);
    // validate page number
    try {
      if (!validNumber(target.substr(0, findColon))) {
        throw myException("Invalid Target Page Number!");
      }
    }
    catch (myException & re) {
      std::cout << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    // store choice
    std::string choice = target.substr(findColon);
    choicesMap.insert(std::make_pair(choice, targetPage));
    choices.push_back(choice);
  }

  int gatStatus() {
    if (win) {
      return 1;
    }
    else if (lose) {
      return 2;
    }
    return 3;
  }
};

#endif
