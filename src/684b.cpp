// Redundant Connection
// Difficulty: Medium
//
// In this problem, a tree is an undirected graph that is connected and has no cycles. You
// are given a graph that started as a tree with n nodes labeled from 1 to n, with one
// additional edge added. The added edge has two different vertices chosen from 1 to n, and
// was not an edge that already existed. The graph is represented as an array edges of
// length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and
// bi in the graph. Return an edge that can be removed so that the resulting graph is a
// tree of n nodes. If there are multiple answers, return the answer that occurs last in
// the input.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
  vector<int> parent;
  vector<int> size;

  int find(int x) {
    // Flatten the structure in the process
    while (x != parent[x]) {
      parent[x] = parent[parent[x]];
      x = parent[x];
    }
    return x;
  }

  bool unite(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);

    if (root_a == root_b) {
      return false;
    }

    if (size[root_a] < size[root_b]) {
      swap(root_a, root_b);
    }

    parent[root_b] = root_a;
    size[root_a] += size[root_b];
    return true;
  }

public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    // Union-find style problem
    int n = edges.size();

    parent.resize(n + 1);
    size.assign(n + 1, 1);

    for (int i = 1; i <= n; i++) {
      // Undirected beginning
      // all nodes are their own parent
      parent[i] = i;
    }

    for (auto &e : edges) {
      if (!unite(e[0], e[1])) {
        // This edge was connected before
        return e;
      }
    }
    return {};
  }
};

int main() {
  Solution solution;

  {
    vector<vector<int>> edges = vector<vector<int>>{{1, 2}, {1, 3}, {2, 3}};
    vector<int> expected = vector<int>{2, 3};
    std::cout << "Input:    " << str(edges) << '\n';
    auto ans = solution.findRedundantConnection(edges);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> edges = vector<vector<int>>{{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    vector<int> expected = vector<int>{1, 4};
    std::cout << "Input:    " << str(edges) << '\n';
    auto ans = solution.findRedundantConnection(edges);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
