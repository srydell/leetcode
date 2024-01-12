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

class Solution {
public:
  vector<int> asteroidCollision(vector<int> &asteroids) {
    vector<int> out;
    stack<int> stones;
    for (size_t i = 0; i < asteroids.size(); i++) {
      auto a = asteroids[i];
      if (a > 0) {
        // Moving to the right
        stones.push(a);
      } else if (a < 0) {
        // Check if it collides with something
        // Smash the stones to the left : )
        bool broken = false;
        while (!stones.empty() && stones.top() > 0) {
          if (stones.top() == std::abs(a)) {
            broken = true;
            stones.pop();
            break;
          }

          if (stones.top() > std::abs(a)) {
            break;
          }
          stones.pop();
        }

        if (!broken && (stones.empty() || stones.top() < 0)) {
          stones.push(a);
        }
      }
    }

    while (!stones.empty()) {
      out.push_back(stones.top());
      stones.pop();
    }

    reverse(out.begin(), out.end());
    return out;
  }
};

int main() {
  Solution solution;

  {
    vector<int> asteroids = {5, 10, -5};
    auto ans = solution.asteroidCollision(asteroids);
    std::cout << "Input:    " << str(asteroids) << '\n';
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector<int>{5, 10}) << '\n';
  }

  {
    vector<int> asteroids = {8, -8};
    auto ans = solution.asteroidCollision(asteroids);
    std::cout << "Input:    " << str(asteroids) << '\n';
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector<int>{}) << '\n';
  }

  {
    vector<int> asteroids = {10, 2, -5};
    auto ans = solution.asteroidCollision(asteroids);
    std::cout << "Input:    " << str(asteroids) << '\n';
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector<int>{10}) << '\n';
  }

  {
    vector<int> asteroids = {-5, -5};
    auto ans = solution.asteroidCollision(asteroids);
    std::cout << "Input:    " << str(asteroids) << '\n';
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector<int>{-5, -5}) << '\n';
  }
}
