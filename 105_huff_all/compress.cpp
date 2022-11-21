#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream f(inFile);
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  char ch;
  while (f.get(ch)) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find((unsigned char)ch);
    assert(it != theMap.end());
    bfw.writeBitString(it->second);
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  assert(theMap.find(256) != theMap.end());
  bfw.writeBitString(theMap.find(256)->second);

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  f.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  const char * inFile = argv[1];
  const char * outFile = argv[2];
  uint64_t * counts = readFrequencies(inFile);
  Node * myTree = buildTree(counts);
  BitString bs;
  std::map<unsigned, BitString> theMap;
  myTree->buildMap(bs, theMap);
  writeCompressedOutput(inFile, outFile, theMap);
  delete myTree;
  delete[] counts;
  return EXIT_SUCCESS;
}
