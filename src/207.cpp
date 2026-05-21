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
    // I'm going to model this as a directed graph.
    //
    // prerequisites[i] = [a, b]
    // means
    //   b -> a
    //
    //   because to take course a, we must first take b.
    //
    // The core observation is:
    // WE can finish all courses iff the graph has NO cycles.
    //
    vector<vector<int>> graph(numCourses);

    // Build adjacency list
    for (auto &p : prerequisites) {
      int course = p[0];
      int prereq = p[1];
      graph[prereq].push_back(course);
    }

    // I'll use a 3-state DSF visitation scheme.
    //
    // 0 = unvisited
    // 1 = currently visiting (in recursion stack)
    // 2 = fully processed
    //
    // The important invariant is:
    // Iif we ever reach a node already  marked visiting,
    // then we've found a cycle.
    //
    vector<int> state(numCourses, 0);

    // The graph may be disconnected,
    // so I need to DSF from every node.
    for (int course = 0; course < numCourses; course++) {
      // Only start DSF from unvisited nodes
      if (state[course] == 0) {
        // If any DSF detects a cycle,
        // then it's impossible to finish all courses
        if (hasCycle(course, graph, state)) {
          return false;
        }
      }
    }

    // If no cycles were found anywhere in the graph,
    // then a valid ordering exists
    return true;
  }

private:
  bool hasCycle(int course, vector<vector<int>> &graph, vector<int> &state) {
    // Iif we revesit a node currently in the recursion stack,
    // then we found a back edge => cycle.
    if (state[course] == 1) {
      return true;
    }

    // If this node is already fully processed
    // We already know no cycle exists downstream from it.
    //
    // This avoids repeated work.
    if (state[course] == 2) {
      return false;
    }

    // Mark node as currently being explored
    state[course] = 1;

    // Explore all outgoing edges
    for (int next : graph[course]) {
      // If any child path finds a cycle
      // propagate failure upward immediately
      if (hasCycle(next, graph, state)) {
        return true;
      }
    }

    // We have now fully explored this node
    // and confirmed no cycles exist below it.
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
