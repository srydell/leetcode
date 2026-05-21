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
public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    // If there is a cycle within the graph of courses, then it's impossible to complete all courses.
    //
    // Let's build an adjency list
    vector<vector<int>> graph(numCourses, vector<int>{});
    for (int i = 0; i < prerequisites.size(); i++) {
      int course = prerequisites[i][0];
      int prereq = prerequisites[i][1];

      graph[prereq].push_back(course);
    }

    // Let's keep state over each course we've already explored for cycles such that
    //
    // state[course] = 0, unvisited
    // state[course] = 1, visited within this exploration
    // state[course] = 2, fully explored
    //
    // The final state avoids extra explorations
    vector<int> state(numCourses, 0);

    // Since the graph can be disconnected, we need to explore every course
    for (int course = 0; course < numCourses; course++) {
      if (state[course] == 0) {
        if (hasCycle(course, graph, state)) {
          return false;
        }
      }
    }

    // There were no cycles found, must be possible to do all courses
    return true;
  }

private:
  bool hasCycle(int course, vector<vector<int>> &graph, vector<int> &state) {
    // If this recursion visited a course already visited there is a cycle
    if (state[course] == 1) {
      return true;
    }

    // If this part of the graph is already visited prior
    if (state[course] == 2) {
      return false;
    }

    // Mark as being explored
    state[course] = 1;

    // Look at adjacent courses
    for (int c : graph[course]) {
      if (hasCycle(c, graph, state)) {
        // Report immediately
        return true;
      }
    }

    // Mark as safe
    state[course] = 2;

    return false;
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
