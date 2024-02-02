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

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *create(vector<int> const &v) {
  ListNode *head = new ListNode();
  ListNode *current = head;
  for (size_t i = 0; i < v.size(); i++) {
    current->val = v[i];
    if (i != v.size() - 1) {
      current->next = new ListNode();
    }
    current = current->next;
  }
  return head;
}

string str(ListNode const *head) {
  std::stringstream ss;
  ss << '[';

  while (head) {
    ss << head->val;
    if (head->next) {
      ss << ", ";
    }
    head = head->next;
  }

  ss << ']';
  return ss.str();
}

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
  int pairSum(ListNode *head) {
    int maxSum = numeric_limits<int>::min();

    stack<int> values;

    auto current = head;
    while (current) {
      values.push(current->val);
      current = current->next;
    }

    current = head;
    auto size = values.size();
    for (size_t i = 0; i < size / 2; i++) {
      maxSum = max(current->val + values.top(), maxSum);
      values.pop();
      current = current->next;
    }

    return maxSum;
  }
};

int main() {
  Solution solution;

  {
    auto head = create(vector<int>{5, 4, 2, 1});
    std::cout << "Input:    " << str(head) << '\n';
    auto ans = solution.pairSum(head);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 6 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    auto head = create(vector<int>{4, 2, 2, 3});
    std::cout << "Input:    " << str(head) << '\n';
    auto ans = solution.pairSum(head);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 7 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    auto head = create(vector<int>{1, 100000});
    std::cout << "Input:    " << str(head) << '\n';
    auto ans = solution.pairSum(head);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 100001 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
