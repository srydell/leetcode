// Design Hit Counter
// Difficulty: Medium

#include "helpers.hpp"

#include <ctime>
#include <iostream>
#include <queue>

using namespace std;
class HitCounter {
public:
  HitCounter() {
  }

  void hit(int timestamp) {
    hits.push(timestamp);
  }

  int getHits(int timestamp) {
    while (!hits.empty() && hits.front() <= timestamp - 300) {
      hits.pop();
    }

    return hits.size();
  }

private:
  queue<int> hits;
};

int main() {
  {
    std::cout << "Example 1" << '\n';
    std::cout << "Step 1: HitCounter()" << '\n';
    HitCounter obj{};
    std::cout << "Step 2: hit(1)" << '\n';
    obj.hit(1);
    std::cout << "Step 3: hit(2)" << '\n';
    obj.hit(2);
    std::cout << "Step 4: hit(3)" << '\n';
    obj.hit(3);
    std::cout << "Step 5: getHits(4)" << '\n';
    auto ans5 = obj.getHits(4);
    std::cout << "Got:      " << ans5 << '\n';
    std::cout << "Step 6: hit(300)" << '\n';
    obj.hit(300);
    std::cout << "Step 7: getHits(300)" << '\n';
    auto ans7 = obj.getHits(300);
    std::cout << "Got:      " << ans7 << '\n';
    std::cout << "Step 8: getHits(301)" << '\n';
    auto ans8 = obj.getHits(301);
    std::cout << "Got:      " << ans8 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
