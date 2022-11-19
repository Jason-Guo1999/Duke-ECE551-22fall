#include <cstdlib>
#include <iostream>

#include "Story.cpp"
#include "Story.hpp"
#include "helperFunction.hpp"
#include "myException.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Error command!" << std::endl;
    exit(EXIT_FAILURE);
  }
  // initialize story from directory
  Story myStory(argv[1]);
  // verify story
  try {
    if (!myStory.checkStory()) {
      throw(myException("Invalid story!"));
    }
  }
  catch (myException & re) {
    std::cerr << re.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  // start from page 0
  std::vector<std::vector<std::string> > ans;
  std::vector<std::string> tempAns;
  std::unordered_set<size_t> visited;
  myStory.findWinPath(ans, tempAns, visited, 0);
  printWinPath(ans);
  return EXIT_SUCCESS;
}
