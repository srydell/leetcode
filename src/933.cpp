#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class RecentCounter {
public:
  RecentCounter() {}
  int ping(int t) {
    pings.push_back(t);
    auto it = std::ranges::lower_bound(pings, t - 3000);

    return static_cast<int>(distance(it, pings.end()));
  }

  vector<int> pings;
};

template <typename T> string str(vector<T> const &v) {
  std::stringstream ss;
  ss << '[';
  for (size_t i = 0; i < v.size(); i++) {
    ss << v[i];
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

int main() {
  RecentCounter solution;

  {
    std::cout << "Got:      "
              << str(vector<int>{solution.ping(1), solution.ping(100),
                                 solution.ping(3001), solution.ping(3002)})
              << '\n';
    std::cout << "Expected: "
              << "[1, 2, 3, 3]" << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
