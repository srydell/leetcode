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
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    // Topological sort with cycle detection over the courses
    // Use Kahn's algo

    // Create adjacency list
    vector<vector<int>> graph(numCourses, vector<int>{});
    for (int i = 0; i < prerequisites.size(); i++) {
      int course = prerequisites[i][0];
      int prereq = prerequisites[i][1];

      graph[prereq].push_back(course);
    }

    // Create the number of indegrees for each course
    // Kahn's algo works such that we pop every node (course)
    // with indigree = 0, that may remove indigrees for other nodes, which reiterates the work.
    // If there are nodes with indigree >0 in the end, there is a cycle.
    vector<int> indegree(numCourses, 0);

    for (int course = 0; course < numCourses; course++) {
      for (auto n : graph[course]) {
        // How many dependencies does n have?
        indegree[n]++;
      }
    }

    queue<int> q;
    for (int course = 0; course < numCourses; course++) {
      if (indegree[course] == 0) {
        // Ready to be removed
        q.push(course);
      }
    }

    vector<int> order;

    while (!q.empty()) {
      int course = q.front();
      q.pop();

      // NOTE: in queue = ready to be pushed
      order.push_back(course);

      for (auto n : graph[course]) {
        indegree[n]--;
        if (indegree[n] == 0) {
          q.push(n);
        }
      }
    }

    if (order.size() != numCourses) {
      return {}; // Cycle
    }

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
