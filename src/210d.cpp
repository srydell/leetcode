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
#include <queue>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    // Topological sort over the course adjacency list. Use Kahn's algo.
    // It works with number of indegrees per node. If a node has 0 indegree (no prerequisites),
    // then it can be placed in order (i.e. taking the course). That then unlocks other courses
    // which now has their indegree lowered (due to prerequisite taken). If every course has indegree 0
    // at the end, then there are no cycles and it's possible to pass all courses.
    //
    // Build adjacency list first

    vector<vector<int>> graph(numCourses, vector<int>{});
    for (int i = 0; i < prerequisites.size(); i++) {
      int course = prerequisites[i][0];
      int prereq = prerequisites[i][1];

      graph[prereq].push_back(course);
    }

    // Build indegrees
    vector<int> indegree(numCourses, 0);
    for (int course = 0; course < numCourses; course++) {
      for (int n : graph[course]) {
        // "In order to take course n, one more course has to be taken"
        indegree[n]++;
      }
    }

    // Queue of courses ready to be taken
    queue<int> q;
    for (int course = 0; course < numCourses; course++) {
      if (indegree[course] == 0) {
        q.push(course);
      }
    }

    vector<int> order;

    // Now just go through the courses able to be taken one at a time
    while (!q.empty()) {
      int course = q.front();
      q.pop();

      order.push_back(course);

      // Course taken, adjust indegrees
      for (auto n : graph[course]) {
        indegree[n]--;
        if (indegree[n] == 0) {
          q.push(n);
        }
      }
    }

    // Cycle?
    if (order.size() != numCourses) {
      return {};
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
