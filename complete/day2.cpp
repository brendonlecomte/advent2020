#include "fileReader.h"
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

struct pwd_data {
  int min;
  int max;
  std::string req;
  std::string password;

  void print() {
    std::cout << password << std::endl;
    std::cout << min << std::endl;
    std::cout << max << std::endl;
    std::cout << req << std::endl;
  }

  bool isValid() {
    char _req = req[0];

    // both arent the same. required!
    if (password[min - 1] == password[max - 1])
      return false;
    // One, at least, must be REQ
    if (password[min - 1] != _req && password[max - 1] != _req)
      return false;

    return true;
  }

  bool isValid_part1() {
    auto x = std::count(password.begin(), password.end(), req[0]);
    if (x < min)
      return false;
    if (x > max)
      return false;
    return true;
  }
};

int main() {
  std::vector<pwd_data> passwords;
  // file reader takes a lambda to parse each line. Captures and obj that will
  // be populated.
  fileReader(
      "/users/brendon/research/advent-of-code-2020/day2-input.txt",
      [&passwords](std::string line) {
        passwords.push_back(
            {.min = std::stoi(line.substr(0, line.find("-"))),
             .max = std::stoi(line.substr(line.find("-") + 1, line.find(" "))),
             .req = line.substr(line.find(": ") - 1, 1),
             .password = line.substr(line.find(": ") + 2, line.size())});
      });
  int count = 0;
  for (auto &x : passwords) {
    if (x.isValid()) {
      count++;
      x.print();
    }
  }
  std::cout << count << std::endl;
  return 0;
}
