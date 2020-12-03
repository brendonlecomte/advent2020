#include "fileReader.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

struct treeMap {
  std::vector<std::vector<int>> tree_map;
  std::pair<int, int> position{0, 0};
  int width = 31; // probably
  int height = 322;

  void print() {
    std::cout << "Height: " << tree_map.size() << std::endl;
    std::cout << "Width: " << tree_map[0].size() << std::endl;
    auto print_row = [](std::vector<int> &row) {
      for (auto &x : row) {
        std::cout << x;
      }
      std::cout << std::endl;
    };
    print_row(tree_map[0]);
    print_row(tree_map[1]);
    print_row(tree_map[2]);
  }

  void reset() {
    position = std::pair<int, int>{0, 0};
    height = tree_map.size() - 1; // heigh is one less than size
    // use size below because it gets modulo'd in the math
    width = tree_map[0].size();
  }

  std::pair<int, int> step(std::pair<int, int> slope) {
    auto [x, y] = position;
    x = x + std::get<0>(slope);
    int _y = y + std::get<1>(slope);
    y = _y % width;
    position = std::pair<int, int>{x, y};
    return position;
  }

  bool isTree() {
    return (tree_map[std::get<0>(position)][std::get<1>(position)] == 1);
  }

  bool isBottom() { return (std::get<0>(position) == height); }

  int traverse(std::pair<int, int> sl) {
    int count = 0;
    while (!isBottom()) {
      step(sl);
      if (isTree())
        count++;
    }
    return count;
  }
};

int main() {
  struct treeMap map;
  // file reader takes a lambda to parse each line. Captures and obj that will
  // be populated.
  fileReader("/users/brendon/research/advent-of-code-2020/day3-input.txt",
             [&map](std::string line) {
               std::vector<int> row;
               for (auto &sq : line) {
                 row.push_back((sq == '#') ? 1 : 0);
               }
               map.tree_map.push_back(row);
             });

  // std::vector<std::pair<int, int>> slopes = {{1,3}};
  map.reset();
  map.print();
  std::vector<std::pair<int, int>> slopes = {
      {1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1},
  };

  std::vector<int> trees;
  for (auto &sl : slopes) {
    int count = map.traverse(sl);
    trees.push_back(count);
    std::cout << "Trees: " << count << std::endl;
    map.reset();
  }
  auto total = std::accumulate(trees.begin(), trees.end(), 1LL,
                               std::multiplies<long long int>());
  std::cout << "Total: " << total << std::endl;

  return 0;
}
