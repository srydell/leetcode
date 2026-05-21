// Fruit Into Baskets
// Difficulty: Medium
//
// You are visiting a farm that has a single row of fruit trees arranged from
// left to right. The trees are represented by an integer array fruits where
// fruits[i] is the type of fruit the ith tree produces. You want to collect as
// much fruit as possible. However, the owner has some strict rules that you
// must follow: You only have two baskets, and each basket can only hold a
// single type of fruit. There is no limit on the amount of fruit each basket
// can hold. Starting from any tree of your choice, you must pick exactly one
// fruit from every tree (including the start tree) while moving to the right.
// The picked fruits must fit in one of your baskets. Once you reach a tree with
// fruit that cannot fit in your baskets, you must stop. Given the integer array
// fruits, return the maximum number of fruits you can pick.

#include "helpers.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;
class Solution {
public:
  int totalFruit(vector<int> &fruits) {
    // Variable size sliding window problem
    // Invariant: Valid window only contains two types of fruit.
    // Move the right pointer until there are three types of fruit. Then move
    // the left until the window is valid again. Keep track of the length of the
    // window. Want to know the maximum lenght of the window.
    int best = 0;
    int left = 0;
    unordered_map<int, int> picked;

    for (int right = 0; right < fruits.size(); right++) {
      picked[fruits[right]]++;
      while (picked.size() > 2) {
        // Remove from the left
        picked[fruits[left]]--;
        if (picked[fruits[left]] == 0) {
          picked.erase(fruits[left]);
        }
        left++;
      }

      best = std::max(best, right - left + 1);
    }
    return best;
  }
};

int main() {
  Solution solution;

  {
    // We can pick from all 3 trees.
    vector<int> fruits = vector<int>{1, 2, 1};
    int expected = 3;
    std::cout << "Input:    " << str(fruits) << '\n';
    auto ans = solution.totalFruit(fruits);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // We can pick from trees [1,2,2]. If we had started at the first tree, we
    // would only pick from trees [0,1].
    vector<int> fruits = vector<int>{0, 1, 2, 2};
    int expected = 3;
    std::cout << "Input:    " << str(fruits) << '\n';
    auto ans = solution.totalFruit(fruits);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // We can pick from trees [2,3,2,2]. If we had started at the first tree, we
    // would only pick from trees [1,2].
    vector<int> fruits = vector<int>{1, 2, 3, 2, 2};
    int expected = 4;
    std::cout << "Input:    " << str(fruits) << '\n';
    auto ans = solution.totalFruit(fruits);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
