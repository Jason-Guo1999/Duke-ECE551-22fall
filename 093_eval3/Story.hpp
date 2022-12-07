#ifndef _STORYHPP_
#define _STORYHPP_
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "Page.cpp"
#include "Page.hpp"
class Story {
 private:
  // a pageMap is used to store key-value relation between pageNum and page
  std::map<int, Page> pageMap;

  // total pageNum
  size_t totalPages;

  // store the item get form each page, update when reading a new page
  std::map<std::string, long> itemList;

 public:
  // build story thorugh a directory
  Story(const char * directory);

  // verify the whole story
  bool checkStory();

  // print Story : step1
  void printPages();

  // display story : step2,4
  void displayStory(size_t currentPage);

  // step3: find win path
  void findWinPath(std::vector<std::vector<std::string> > & ans,
                   std::vector<std::string> & tempAns,
                   std::set<size_t> & visited,
                   size_t currentPageNumber);

  // valid choice status
  bool validChoiceStatus(Choice & targetChoice) {
    return targetChoice.validPrerequisite(itemList);
  }

  // update item list when entering new page
  void updateItemList(Page & page);
};

#endif
