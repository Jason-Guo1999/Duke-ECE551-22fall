#include <cstdlib>
#include <iostream>

#include "Story.h"
#include "myException.h"

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
  myStory.displayStory(0);
  return EXIT_SUCCESS;
}
