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
  vector<int> parent; // parent links
  vector<int> size; // Size of tree

  int find(int x) {
    // Find the root of the group that x is in
    while (x != parent[x]) {
      // Path halfing
      parent[x] = parent[parent[x]];
      x = parent[x];
    }
    return x;
  }

  bool unite(int a, int b) {
    int ra = find(a);
    int rb = find(b);

    if (ra == rb) {
      // Already connected.
      return false;
    }

    if (size[ra] < size[rb]) {
      swap(ra, rb);
    }

    // "b cluster now belongs to a"
    size[ra] += size[rb];
    parent[rb] = ra;
    return true;
  }

public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    // Union find style of problem
    // unite edges until two of them are already united previously
    int n = edges.size();
    parent.resize(n + 1);
    // All sizes are 1 initially
    size.assign(n + 1, 1);

    // Initialize parent
    for (int i = 1; i <= n; i++) {
      parent[i] = i;
    }

    for (auto &e : edges) {
      int u = e[0];
      int v = e[1];

      if (!unite(u, v)) {
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
