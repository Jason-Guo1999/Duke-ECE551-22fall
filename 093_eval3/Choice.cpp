#include "Choice.hpp"

Choice::Choice(std::string s, int mode) {
  // initialize choice from 2 modes
  if (mode == 1) {
    content = s;
  }
  else {
    size_t findLeftParenthese = s.find('[');
    size_t findRightParenthese = s.find(']');
    size_t findFirstColon = s.find(':');
    size_t findSecondColon = s.substr(findFirstColon + 1).find(':');
    content = s.substr(findFirstColon + findSecondColon + 2);
    size_t findEqual = s.find('=');
    try {
      if (findLeftParenthese == std::string::npos ||
          findRightParenthese == std::string::npos ||
          findFirstColon == std::string::npos || findSecondColon == std::string::npos ||
          findEqual == std::string::npos) {
        throw myException("Invalid line format : special choice line 1");
      }
      else if (findFirstColon < findRightParenthese ||
               !(findEqual > findLeftParenthese && findEqual < findRightParenthese)) {
        throw myException("Invalid line format : special choice line 2");
      }
    }
    catch (myException & re) {
      std::cerr << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    std::pair<std::string, long> tempPrerequisite;
    tempPrerequisite.first =
        s.substr(findLeftParenthese + 1, findEqual - findLeftParenthese - 1);
    tempPrerequisite.second = strtol(
        s.substr(findEqual + 1, findRightParenthese - findEqual - 1).c_str(), NULL, 10);
    try {
      if (!validNumber(s.substr(findEqual + 1, findRightParenthese - findEqual - 1))) {
        throw myException("Invalid Prerequisites : Invalid number");
      }
    }
    catch (myException & re) {
      std::cerr << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }

    prerequisites.insert(tempPrerequisite);
  }
}

bool Choice::validPrerequisite(std::map<std::string, long> & itemList) {
  std::map<std::string, long>::iterator it = itemList.begin();
  while (it != prerequisites.end()) {
    if (!itemList.count((*it).first) && (*it).second != 0) {
      return false;
    }
    else if ((*it).second != itemList[(*it).first]) {
      return false;
    }
    else {
      ++it;
    }
  }
  return true;
}
