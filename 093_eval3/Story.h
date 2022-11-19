#ifndef _STORYH_
#define _STORYH_
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Page.h"
#include "helperFunction.h"
#include "myException.h"
class Story {
 public:
  std::unordered_map<int, Page> pageMap;
  size_t totalPages;
  // store the item get form each page, update when reading a new page
  std::unordered_map<std::string, long> itemList;
  // build story thorugh a directory

  Story(const char * directory) {
    // item list is empty at the beginning
    //itemList = std::unordered_map<std::string, long>();
    // find the story.txt file
    const std::string storyFile = "/story.txt";
    const std::string tempStoryPath = directory + storyFile;
    const char * storyPath = tempStoryPath.c_str();
    if (!findFile(storyPath)) {
      std::cerr << "Can't find story.txt in this directory!" << std::endl;
      exit(EXIT_FAILURE);
    }
    // open the story.txt
    std::ifstream st;
    st.open(storyPath);
    std::string line;
    // read story.txt to fill each pages
    // indicate we read a "@"
    bool at = false;
    totalPages = 0;
    while (!st.eof()) {
      size_t pageNum = 0;
      std::getline(st, line);
      // blank line : ignore
      if (line.size() == 0) {
        continue;
      }
      // decide line mode : choice or content
      int lineMode = decideLineMode(line);
      /*
	we have four line modes :
	1: @ page content
	2: : page normal choice
	3: $ item change 
	4: [ page special choice
       */
      if (lineMode == 1) {
        size_t findAt = line.find('@');
        pageNum = std::strtoull(line.substr(0, findAt).c_str(), NULL, 10);
        // if we don't start from page0, throw an exception
        try {
          // test valid number and valid line format
          if (!validNumber(line.substr(0, findAt))) {
            throw myException("Invalid PageNum type1");
          }
          if (pageNum != 0 && !at) {
            throw myException("Story don't start at page 0!");
          }
          if (pageNum != totalPages) {
            throw myException("Invalid pageNum! uncontigous page initialization!");
          }
          if (line.find(':') == std::string::npos) {
            throw myException("Invalid line format: missing ':' in content line!");
          }
        }
        catch (myException & re) {
          std::cout << re.what() << std::endl;
          exit(EXIT_FAILURE);
        }
        // if we start from page0, turn at to true
        if (pageNum == 0) {
          at = true;
        }
        // create a new page
        Page newPage(line, directory);
        // add it to hashmap
        pageMap.insert({totalPages, newPage});
        totalPages++;
      }
      // read choices
      else if (lineMode == 2) {
        size_t firstColon = line.find(':');
        if (firstColon == std::string::npos) {
          std::cerr << "Invalid input format : can't find first ':' in choices line"
                    << std::endl;
        }
        size_t secondColon = line.substr(firstColon + 1).find(':');
        if (secondColon == std::string::npos) {
          std::cerr << "Invalid input format : can't find second ':' in choices line"
                    << std::endl;
        }
        pageNum = strtoull(line.substr(0, firstColon).c_str(), NULL, 10);
        // if we trying to visit an uninitilized page, throw exception
        try {
          if (!validNumber(line.substr(0, firstColon))) {
            throw myException("Invalid Pagenum type2");
          }
          if (!pageMap.count(pageNum)) {
            throw myException("Page undeclared!");
          }
        }
        catch (myException & re) {
          std::cerr << re.what() << std::endl;
          exit(EXIT_FAILURE);
        }
        // get choices for corresponding page -> mode1
        pageMap[pageNum].getChoices(line.substr(firstColon + 1), 1);
      }
      else if (lineMode == 3) {
        // item change in corresponding page
        size_t findDollar = line.find('$');
        pageNum = strtoll(line.substr(0, findDollar).c_str(), NULL, 10);
        // if we trying to visit an uninitilized page, throw exception
        try {
          if (!validNumber(line.substr(0, findDollar))) {
            throw myException("Invalid Pagenum type3");
          }
          if (!pageMap.count(pageNum)) {
            throw myException("Page undeclared!");
          }
        }
        catch (myException & re) {
          std::cerr << re.what() << std::endl;
          exit(EXIT_FAILURE);
        }
        // store item change to corresponding page
        pageMap[pageNum].storeItemChange(line.substr(findDollar + 1));
      }
      else if (lineMode == 4) {
        // get special choice form line
        size_t findLeftParenthese = line.find('[');
        pageNum = strtoll(line.substr(0, findLeftParenthese).c_str(), NULL, 10);
        // if we trying to visit an uninitilized page, throw exception
        try {
          if (!validNumber(line.substr(0, findLeftParenthese))) {
            throw myException("Invalid Pagenum type4!");
          }
          if (!pageMap.count(pageNum)) {
            throw myException("Page undeclared!");
          }
        }
        catch (myException & re) {
          std::cerr << re.what() << std::endl;
          exit(EXIT_FAILURE);
        }
        // get choices from current line -> mode2
        pageMap[pageNum].getChoices(line.substr(findLeftParenthese), 2);
      }
      else {
        // can't find proper line mode
        std::cerr << "Invalid line: can't find line mdoe!" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }

  // verify the whole story
  bool checkStory() {
    bool haveWin = false;
    bool haveLose = false;
    // store pages that be referenced
    std::unordered_set<int> validate;
    // page1 may not be referenced
    validate.insert(0);
    for (size_t i = 0; i < pageMap.size(); i++) {
      // get a win page
      if (pageMap[i].getStatus() == 1) {
        haveWin = true;
        continue;
      }
      // get a lose page
      if (pageMap[i].getStatus() == 2) {
        haveLose = true;
        continue;
      }
      // get a normal page
      for (Choice & choice : pageMap[i].choices) {
        size_t targetPage = pageMap[i].choicesMap[choice.getChoiceContent()];
        try {
          if (targetPage < 0 || targetPage >= pageMap.size()) {
            throw(myException("Invalid choice! error target pageNum"));
          }
        }
        catch (myException & re) {
          std::cerr << re.what() << std::endl;
          exit(EXIT_FAILURE);
        }

        if (!validate.count(targetPage)) {
          validate.insert(targetPage);
        }
      }
    }
    // every page is referenced at least once
    try {
      if (validate.size() != pageMap.size()) {
        throw(myException("Found unreferenced page!"));
      }
    }
    catch (myException & re) {
      std::cerr << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    // have win page
    try {
      if (!haveWin) {
        throw(myException("Missing win page"));
      }
    }
    catch (myException & re) {
      std::cerr << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    // have lose page
    try {
      if (!haveLose) {
        throw(myException("Missing lose page"));
      }
    }
    catch (myException & re) {
      std::cerr << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    return true;
  }
  // print Story

  void printPages() {
    for (size_t i = 0; i < pageMap.size(); i++) {
      std::cout << "Page " << i << std::endl;
      std::cout << "==========" << std::endl;
      pageMap[i].printPageContent();
      if (pageMap[i].getStatus() == 1) {
        std::cout << "Congratulations! You have won. Hooray!" << std::endl;
      }
      else if (pageMap[i].getStatus() == 2) {
        std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
      }
      else {
        for (size_t j = 0; j < pageMap[i].choices.size(); j++) {
          std::cout << j + 1 << "." << pageMap[i].choices[j].getChoiceContent()
                    << std::endl;
        }
      }
    }
  }

  // display story
  void displayStory(size_t currentPage) {
    Page & page = pageMap[currentPage];
    updateItemList(page);
    page.printPageContent();
    // if we win or lose, print result
    std::cout << std::endl;
    if (page.getStatus() == 1 || page.getStatus() == 2) {
      if (page.getStatus() == 1) {
        std::cout << "Congratulations! You have won. Hooray!" << std::endl;
        return;
      }
      else {
        std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
        return;
      }
    }

    // else, print choices
    else {
      std::cout << "What would you like to do?" << std::endl;
      std::cout << std::endl;
      for (size_t i = 1; i < page.choices.size() + 1; i++) {
        if (!validChoiceStatus(page.choices[i - 1])) {
          std::cout << i << "."
                    << "<UNAVAILIABLE>" << std::endl;
        }
        else {
          std::cout << i << "." << page.choices[i - 1].getChoiceContent() << std::endl;
        }
      }
    }

    // make a choice
    size_t readerChoice;
    while (true) {
      size_t temp;
      std::cin >> temp;
      if (temp <= 0 || temp > page.choices.size()) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
      else if (!validChoiceStatus(page.choices[temp - 1])) {
        std::cout << "That choice is not available at this time, please try again"
                  << std::endl;
      }
      else {
        readerChoice = temp;
        break;
      }
    }
    // transfer to reader's choice
    size_t targetPage =
        page.choicesMap[page.choices[readerChoice - 1].getChoiceContent()];
    displayStory(targetPage);
  }

  void findWinPath(std::vector<std::vector<std::string> > & ans,
                   std::vector<std::string> & tempAns,
                   std::unordered_set<size_t> & visited,
                   size_t currentPageNumber) {
    // backtrace algo
    Page & currentPage = pageMap[currentPageNumber];
    // if reach a win page
    if (currentPage.getStatus() == 1) {
      tempAns.push_back(std::to_string(currentPageNumber) + "(win)");

      ans.push_back(tempAns);
      tempAns.pop_back();
      return;
    }
    if (currentPage.getStatus() == 2) {
      return;
    }
    // if we have visited before : circle
    if (visited.count(currentPageNumber)) {
      return;
    }
    // try to do dfs
    visited.insert(currentPageNumber);
    for (size_t i = 0; i < currentPage.choices.size(); i++) {
      size_t targetPage =
          currentPage.choicesMap[currentPage.choices[i].getChoiceContent()];

      tempAns.push_back(std::to_string(currentPageNumber) + "(" + std::to_string(i + 1) +
                        ")");
      findWinPath(ans, tempAns, visited, targetPage);
      tempAns.pop_back();
    }
    visited.erase(currentPageNumber);
  }

  bool validChoiceStatus(Choice & targetChoice) {
    return targetChoice.validPrerequisite(itemList);
  }

  void updateItemList(Page & page) {
    for (auto it : page.itemListChange) {
      if (itemList.count(it.first)) {
        itemList[it.first] = it.second;
      }
      else {
        itemList.insert(it);
      }
    }
  }
};

#endif
