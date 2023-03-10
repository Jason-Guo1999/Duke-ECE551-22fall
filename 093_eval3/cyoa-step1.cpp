#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Story.cpp"
#include "Story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Error command!" << std::endl;
    exit(EXIT_FAILURE);
  }
  // initialize story from directory
  Story myStory(argv[1]);
  // print the whole story
  myStory.printPages();
  return EXIT_SUCCESS;
}
