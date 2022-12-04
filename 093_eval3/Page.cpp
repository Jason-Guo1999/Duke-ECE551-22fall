#include "Page.hpp"

Page::Page(std::string & s, std::string & directory) {
  size_t findAt = s.find('@');
  size_t findColon = s.find(':');
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
    if (s[findAt + 1] == 'N' && findColon - findAt == 2) {
      win = false;
      lose = false;
    }
    // read a win page
    else if (s[findAt + 1] == 'W' && findColon - findAt == 2) {
      win = true;
      lose = false;
    }
    //read a lose page
    else if (s[findAt + 1] == 'L' && findColon - findAt == 2) {
      win = false;
      lose = true;
    }
    else {
      std::cout << "Invalid State name" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  choices = std::vector<Choice>();
  choicesMap = std::unordered_map<size_t, size_t>();
}

void Page::printPageContent() {
  // print contents firstly
  for (size_t i = 0; i < contents.size(); i++) {
    std::cout << contents[i] << std::endl;
  }
}

void Page::getChoices(std::string & target, int mode) {
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
  if (mode == 1) {
    size_t findColon = target.find(':');
    size_t targetPage = std::strtoll(target.substr(0, findColon).c_str(), nullptr, 10);
    // validate page number
    try {
      if (!validNumber(target.substr(0, findColon))) {
        throw myException("Invalid Target Page Number: page.getchoices mode1");
      }
    }
    catch (myException & re) {
      std::cout << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    // store choice
    Choice newChoice = Choice(target.substr(findColon + 1), mode);
    choices.push_back(newChoice);
    choicesMap.insert({choices.size(), targetPage});
  }
  else if (mode == 2) {
    size_t findFirstColon = target.find(':');
    size_t findSecondColon = target.substr(findFirstColon + 1).find(':');
    size_t targetPage = std::strtoll(
        target.substr(findFirstColon + 1, findSecondColon).c_str(), nullptr, 10);
    try {
      if (!validNumber(target.substr(findFirstColon + 1, findSecondColon))) {
        throw myException("Invalid Target Page Number: page.getchoices mode2!");
      }
    }
    catch (myException & re) {
      std::cout << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    Choice newChoice = Choice(target, mode);
    choices.push_back(newChoice);
    choicesMap.insert({choices.size(), targetPage});
  }
}

int Page::getStatus() {
  if (win) {
    return 1;
  }
  else if (lose) {
    return 2;
  }
  return 3;
}

void Page::storeItemChange(std::string s) {
  // format : xxx=number
  size_t findEqual = s.find('=');
  std::string item = s.substr(0, findEqual);
  std::size_t number = std::strtol(s.substr(findEqual + 1).c_str(), nullptr, 10);
  try {
    if (!validNumber(s.substr(findEqual + 1))) {
      throw myException("Invalid number in item change ,line mode 3");
    }
  }
  catch (myException & re) {
    std::cout << re.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  itemListChange.insert({item, number});
}
