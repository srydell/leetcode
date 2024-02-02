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

class Solution {
public:
  ListNode *oddEvenList(ListNode *head) {
    if (!head || !head->next || !head->next->next) {
      return head;
    }
    // Split into two lists, one odd and one even
    //
    auto odd = head;
    auto even = head->next;
    auto even_start = even;
    while (odd->next && even->next) {
      // Connect the odds and evens
      odd->next = even->next;
      even->next = odd->next->next;
      // Now 'safe' to go to next
      odd = odd->next;
      even = even->next;
    }

    // Connect the two lists
    odd->next = even_start;

    return head;
  }
};

int main() {
  Solution solution;

  {
    auto head = create(vector<int>{1, 2, 3, 4, 5});
    std::cout << "Input:    " << str(head) << '\n';
    auto ans = solution.oddEvenList(head);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(std::vector<int>{1, 3, 5, 2, 4}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    auto head = create(vector<int>{2, 1, 3, 5, 6, 4, 7});
    std::cout << "Input:    " << str(head) << '\n';
    auto ans = solution.oddEvenList(head);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(std::vector<int>{2, 3, 6, 7, 1, 5, 4})
              << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
