#ifndef _PAGEHPP_
#define _PAGEHPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Choice.cpp"
#include "Choice.hpp"
class Page {
 private:
  // indicate if we get win or lose state
  bool win;
  bool lose;
  // store choices
  std::unordered_map<size_t, size_t> choicesMap;
  std::vector<Choice> choices;
  // store contents
  std::vector<std::string> contents;
  // step4 : item list change when reach this page
  std::unordered_map<std::string, long> itemListChange;

 public:
  Page() : win(false), lose(false) {}

  // initialize thorugh a given page.txt
  Page(std::string & s, std::string & directory);

  // print page according to different states
  void printPageContent();

  // read choice from given string
  void getChoices(std::string & target, int mode);

  // get Page status
  int getStatus();

  // step4: store item change at the beginning
  void storeItemChange(std::string s);

  // get choices.size()
  size_t getChoicesSize() { return choices.size(); }

  // get choice content
  std::string getContent(size_t index) { return choices[index].getChoiceContent(); }

  // get target pagenum
  size_t getTargetPage(size_t key) { return choicesMap[key]; }
  // get choice
  Choice & getChoice(size_t index) { return choices[index]; }

  // get item change list
  std::unordered_map<std::string, long> & getItemListChange() { return itemListChange; }
};

#endif
