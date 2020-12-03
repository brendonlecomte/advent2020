#include "fileReader.h"
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

int day1_naive(std::vector<int> raw_data) {
  int sum = 0;
  int idx = 0;
  int a, b, c;
  for (auto first = raw_data.begin(); first < raw_data.end(); first++) {
    for (auto second = first + 1; second < raw_data.end(); second++) {
      if(first[0] + second[0] >= 2020) continue;
      for (auto third = second + 1; third < raw_data.end(); third++) {
        sum = first[0] + second[0] + third[0];
        if (sum == 2020) {
          std::cout << first[0] << " + " << second[0] << " + " << third[0]
                    << " = " << sum << std::endl;
          idx = third - raw_data.begin();
          a = first[0];
          b = second[0];
          c = third[0];
          break;
        }
      }
    }
    if (sum == 2020)
      break;
  }
  std::cout << (a * b * c) << std::endl;
  return 0;
}

int main() {
  std::vector<int> raw_data;

  // file reader takes a lambda to parse each line. Captures and obj that will
  // be populated.
  fileReader(
      "/users/brendon/research/advent-of-code-2020/day1-input.txt",
      [&raw_data](std::string line) { raw_data.push_back(std::stoi(line)); });

  day1_naive(raw_data);
  return 0;
}
