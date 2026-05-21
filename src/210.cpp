// Course Schedule II
// Difficulty: Medium
//
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses -
// 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that
// you must take course bi first if you want to take course ai. For example, the pair [0,
// 1], indicates that to take course 0 you have to first take course 1. Return the ordering
// of courses you should take to finish all courses. If there are many valid answers,
// return any of them. If it is impossible to finish all courses, return an empty array.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
  bool dfs(int course, vector<vector<int>> &graph, vector<int> &state, vector<int> &order) {
    state[course] = 1; // Visiting

    for (auto neighbor : graph[course]) {
      if (state[neighbor] == 1) {
        return true; // Cycle found
      }

      if (state[neighbor] == 0) {
        if (dfs(neighbor, graph, state, order)) {
          return true;
        }
      }
    }

    state[course] = 2; // processed
    order.push_back(course);
    return false;
  }

public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    // Create an adjacency list where graph[course] = which courses gets unlocked
    vector<vector<int>> graph(numCourses, vector<int>{});
    for (int i = 0; i < prerequisites.size(); i++) {
      int course = prerequisites[i][0];
      int prereq = prerequisites[i][1];
      graph[prereq].push_back(course);
    }

    // If the graph has a cycle it's impossible to complete all courses
    // Otherwise we should return the topological sort of each course cluster

    // Keep a state map over every course
    // 0 -> unvisited
    // 1 -> currently visiting
    // 2 -> fully explored
    vector<int> state(numCourses, 0);

    vector<int> order;

    // Note: Go through all courses as there can be disjoint course clusters
    for (int course = 0; course < numCourses; course++) {
      if (state[course] == 0) {
        if (dfs(course, graph, state, order)) {
          // Cycle detected
          return {};
        }
      }
    }
    reverse(order.begin(), order.end());
    return order;
  }
};

int main() {
  Solution solution;

  {
    // There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
    int numCourses = 2;
    vector<vector<int>> prerequisites = vector<vector<int>>{{1, 0}};
    vector<int> expected = vector<int>{0, 1};
    std::cout << "Input:    " << numCourses << ", " << str(prerequisites) << '\n';
    auto ans = solution.findOrder(numCourses, prerequisites);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
    int numCourses = 4;
    vector<vector<int>> prerequisites = vector<vector<int>>{{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    vector<int> expected = vector<int>{0, 2, 1, 3};
    std::cout << "Input:    " << numCourses << ", " << str(prerequisites) << '\n';
    auto ans = solution.findOrder(numCourses, prerequisites);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int numCourses = 1;
    vector<vector<int>> prerequisites = vector<vector<int>>{};
    vector<int> expected = vector<int>{0};
    std::cout << "Input:    " << numCourses << ", " << str(prerequisites) << '\n';
    auto ans = solution.findOrder(numCourses, prerequisites);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
