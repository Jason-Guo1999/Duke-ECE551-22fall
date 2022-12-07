#ifndef _CHOICEHPP_
#define _CHOICEHPP_

#include <map>
#include <vector>

#include "helperFunction.hpp"
#include "myException.hpp"

class Choice {
 private:
  // choice content : a string
  std::string content;

  // suppose choice have single prerequisites
  std::map<std::string, long> prerequisites;

 public:
  // choice initializr
  Choice(std::string s, int mode);

  // get choice content
  std::string getChoiceContent() { return this->content; }

  // valid items in itemList
  bool validPrerequisite(std::map<std::string, long> & itemList);
};

#endif
