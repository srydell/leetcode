// Course Schedule
// Difficulty: Medium
//
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses -
// 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that
// you must take course bi first if you want to take course ai. For example, the pair [0,
// 1], indicates that to take course 0 you have to first take course 1. Return true if you
// can finish all courses. Otherwise, return false.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
  bool hasCycle(int course, vector<vector<int>> &graph, vector<int> &seen) {
    if (seen[course] == 1) {
      return true;
    } else if (seen[course] == 2) {
      return false;
    }

    // Mark exploring
    seen[course] = 1;

    for (auto prereq : graph[course]) {
      if (hasCycle(prereq, graph, seen)) {
        return true;
      }
    }

    // Mark explored
    seen[course] = 2;

    return false;
  }

public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    // We need an adjacency list such that graph[course to unlock] = courses
    // If we find a loop within this adjacency list, it's impossible to finish

    vector<vector<int>> graph(numCourses, vector<int>{});
    for (int i = 0; i < prerequisites.size(); i++) {
      int course = prerequisites[i][0];
      int prereq = prerequisites[i][1];
      graph[prereq].push_back(course);
    }

    // 0 -> unseen
    // 1 -> currently visiting
    // 2 -> fully explored
    vector<int> seen(numCourses, 0);

    // Since there can be many disjoint clusters, go through all courses
    for (int course = 0; course < numCourses; course++) {
      if (hasCycle(course, graph, seen)) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  Solution solution;

  {
    // There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
    int numCourses = 2;
    vector<vector<int>> prerequisites = vector<vector<int>>{{1, 0}};
    bool expected = true;
    std::cout << "Input:    " << numCourses << ", " << str(prerequisites) << '\n';
    auto ans = solution.canFinish(numCourses, prerequisites);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
    int numCourses = 2;
    vector<vector<int>> prerequisites = vector<vector<int>>{{1, 0}, {0, 1}};
    bool expected = false;
    std::cout << "Input:    " << numCourses << ", " << str(prerequisites) << '\n';
    auto ans = solution.canFinish(numCourses, prerequisites);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
