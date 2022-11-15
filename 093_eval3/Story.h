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
  // build story thorugh a directory
  Story(const char * directory) {
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
      size_t findAt = line.find('@');
      // we can find a '@'
      if (findAt != std::string::npos) {
        pageNum = std::strtoull(line.substr(0, findAt).c_str(), NULL, 10);
        // if we don;t start from page0, throw an exception
        try {
          // test valid number
          if (!validNumber(line.substr(0, findAt))) {
            throw myException("Invalid PageNum type1");
          }
          if (pageNum != 0 && !at) {
            throw myException("Story don't start at page 0!");
          }
          if (pageNum != totalPages) {
            throw myException("Invalid pageNum! uncontigous page initialization!");
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
      else {
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
        // get choices for corresponding page
        pageMap[pageNum].getChoices(line.substr(firstColon + 1));
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
    validate.insert(1);
    for (size_t i = 0; i < totalPages + 1; i++) {
      Page & page = pageMap[i];
      // get a win page
      if (page.win) {
        haveWin = true;
        continue;
      }
      // get a lose page
      if (page.lose) {
        haveLose = true;
        continue;
      }
      // get a normal page
      for (std::string & choice : page.choices) {
        size_t targetPage = page.choicesMap[choice];
        try {
          if (targetPage < 1 || targetPage > totalPages) {
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
      if (validate.size() != totalPages) {
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
      pageMap[i].printPage();
    }
  }

  // display story
  void displayStory(int currentPage) {
    Page & page = pageMap[currentPage];
    page.printPage();
    // if win or lose
    if (page.win || page.lose) {
      exit(EXIT_SUCCESS);
    }
    // make a choice
    int readerChoice;
    while (true) {
      size_t temp;
      std::cin >> temp;
      if (temp <= 0 || temp >= page.choices.size()) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
      else {
        readerChoice = temp;
        break;
      }
    }
    // transfer to reader's choice
    int targetPage = page.choicesMap[page.choices[readerChoice]];
    displayStory(targetPage);
  }
};

#endif
