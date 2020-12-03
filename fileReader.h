#include <fstream>
#include <iostream>
#include <string>

template <typename F> void fileReader(const char *filePath, F lambda) {

  std::ifstream inputFile(filePath);
  std::string line;
  while (std::getline(inputFile, line)) {
    lambda(line);
  }

  inputFile.close();
}
