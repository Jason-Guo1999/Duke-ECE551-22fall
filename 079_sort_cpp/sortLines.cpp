#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char ** argv) {
  if (argc == 1) {
    cerr << "Invalid command" << endl;
    exit(EXIT_FAILURE);
  }
  ifstream read;
  for (int i = 1; i < argc; i++) {
    string temp;
    vector<string> input;
    read.open(argv[i]);
    while (!read.eof()) {
      getline(read, temp);
      input.push_back(temp);
    }
    sort(input.begin(), input.end());
    for (size_t i = 0; i < input.size(); i++) {
      cout << input[i] << endl;
    }
    read.close();
    input.clear();
  }
  return EXIT_SUCCESS;
}
