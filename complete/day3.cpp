#include "fileReader.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include <vector>

struct treeMap {
  std::vector<std::vector<int>> tree_map;
  std::pair<int, int> position{0, 0};
  int width = 31; // probably
  int height = 322;
  int slopex = 1;
  int slopey = 3;

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
    position = std::pair<int, int> {0,0};
  }

  std::pair<int, int> step() {
    auto [x, y] = position;
    x = x + slopex;
    int _y = y + slopey;
    y = _y % width;
    position = std::pair<int, int>{x, y};
    return position;
  }

  bool isTree() {
    auto [x, y] = position;
    // std::cout << x << "," << y << std::endl;
    return (tree_map[x][y] == 1);
  }

  bool isBottom() {
    auto [x, y] = position;
    return (x == height);
  }

  int traverse(std::pair<int, int> slope) {
    int count = 0;
    auto [x, y] = slope;
    slopex = x;
    slopey = y;
    while (!isBottom()) {
      auto [x, y] = step();
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

  // map.print();
  //std::vector<std::pair<int, int>> slopes = {{1,3}};
  std::vector<std::pair<int, int>> slopes = {
                                          {1, 1},
                                          {1, 3},
                                          {1, 5},
                                          {1, 7},
                                          {2, 1},
  };

  std::vector<int> trees;
  for (auto &sl : slopes) {
    int count = map.traverse(sl);
    trees.push_back(count);
    std::cout << "Trees: " << count << std::endl;
    map.reset();
  }
  auto total = std::accumulate(trees.begin(), trees.end(), 1LL, std::multiplies<long long int>());
  std::cout << "Total: " << total << std::endl;


  return 0;
}
