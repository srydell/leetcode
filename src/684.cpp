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
  bool dfs(int node, int parent, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &link) {
    // Currently visiting

    visited[node] = true;

    for (auto nei : graph[node]) {
      if (nei == parent) {
        // No need to follow parent links
        continue;
      }

      if (visited[nei]) {
        // Cycle detected
        link = {node, nei};
        return true;
      }

      if (dfs(nei, node, graph, visited, link)) {
        return true;
      }
    }

    return false;
  }

public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    // Just do cycle detection via DFS and return the first cycle detected (it will be the last due to the stack ordering)

    // Build adjacency list
    int n = edges.size();
    vector<vector<int>> graph(n + 1, vector<int>{});
    for (int i = 0; i < n; i++) {
      int a = edges[i][0];
      int b = edges[i][1];

      graph[a].push_back(b);
      graph[b].push_back(a);
    }

    vector<int> link;

    vector<int> visited(n + 1, 0);

    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        if (dfs(i, graph, visited, link)) {
          return link;
        }
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
