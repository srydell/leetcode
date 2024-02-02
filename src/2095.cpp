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

class Solution {
public:
  ListNode *deleteMiddle(ListNode *head) {
    if (!head->next) {
      return nullptr;
    }

    size_t length = 0;
    ListNode *current = head;
    while (current) {
      length++;
      current = current->next;
    }

    auto middle = length / 2;
    ListNode *before = head;
    ListNode *mid = head->next;
    ListNode *after = mid->next;
    for (size_t i = 1; i < middle; i++) {
      before = before->next;
      mid = mid->next;
      after = after->next;
    }

    if (!before) {
      head = head->next;
    } else if (!after) {
      before->next = nullptr;
    } else {
      before->next = after;
    }

    return head;
  }
};

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
  Solution solution;

  {
    auto head = create(std::vector<int>{1, 2, 3, 4});
    auto ans = solution.deleteMiddle(head);
    std::cout << "Input:    " << str(head) << '\n';
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector{1, 2, 4}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    auto head = create(std::vector<int>{2, 1});
    auto ans = solution.deleteMiddle(head);
    std::cout << "Input:    " << str(head) << '\n';
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector{2}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
