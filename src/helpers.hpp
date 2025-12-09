#include <map>
#include <sstream>
#include <string>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template <typename Key, typename Value>
std::string str(std::map<Key, Value> const &m) {
  std::stringstream ss;
  ss << '{' << '\n';
  for (auto const &[key, value] : m) {
    ss << "  " << key << ", " << value << '\n';
  }
  ss << '}';
  return ss.str();
}

template <typename T>
std::string str(std::vector<T> const &v, bool newline = false) {
  std::stringstream ss;
  ss << '[';
  if (newline) {
    ss << '\n';
  }
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    ss << v[static_cast<size_t>(i)];
    if (static_cast<size_t>(i) < v.size() - 1) {
      ss << ", ";
    }
    if (newline) {
      ss << '\n';
    }
  }
  ss << ']';
  return ss.str();
}

template <typename T>
std::string str(std::vector<std::vector<T>> const &v, bool newline = false) {
  std::stringstream ss;
  ss << '[';
  if (newline) {
    ss << '\n';
  }
  for (size_t i = 0; i < v.size(); i++) {
    ss << str(v[i]);
    if (i < v.size() - 1) {
      ss << ", ";
    }
    if (newline) {
      ss << '\n';
    }
  }
  ss << ']';
  return ss.str();
}

std::string str(ListNode const *head) {
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
