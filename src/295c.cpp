// Find Median from Data Stream
// Difficulty: Hard
//
// The median is the middle value in an ordered integer list. If the size of the list is
// even, there is no middle value, and the median is the mean of the two middle values. For
// example, for arr = [2,3,4], the median is 3. For example, for arr = [2,3], the median is
// (2 + 3) / 2 = 2.5. Implement the MedianFinder class: MedianFinder() initializes the
// MedianFinder object. void addNum(int num) adds the integer num from the data stream to
// the data structure. double findMedian() returns the median of all elements so far.
// Answers within 10-5 of the actual answer will be accepted.

#include "helpers.hpp"

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
class MedianFinder {
  // Need a way to keep track of the two middle numbers
  // Keep track via a max heap for the left side of the array and a min heap for the right side.
  priority_queue<int> left; // Max heap;
  priority_queue<int, std::vector<int>, std::greater<>> right;

public:
  MedianFinder() {
  }

  void addNum(int num) {
    // Add it to left
    left.push(num);

    // Fix ordering
    right.push(left.top());
    left.pop();

    // Fix sizes (if previous action was unnecessary)
    if (left.size() < right.size()) {
      left.push(right.top());
      right.pop();
    }
  }

  double findMedian() {
    double l = left.top();
    // Uneven size?
    if (left.size() > right.size()) {
      return l;
    }

    return (l + right.top()) / 2.0;
  }
};

int main() {
  {
    std::cout << "Example 1" << '\n';
    // MedianFinder medianFinder = new MedianFinder(); medianFinder.addNum(1); // arr = [1] medianFinder.addNum(2); // arr = [1, 2] medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2) medianFinder.addNum(3); // arr[1, 2, 3] medianFinder.findMedian(); // return 2.0
    std::cout << "Step 1: MedianFinder()" << '\n';
    MedianFinder obj{};
    std::cout << "Step 2: addNum(1)" << '\n';
    obj.addNum(1);
    std::cout << "Step 3: addNum(2)" << '\n';
    obj.addNum(2);
    std::cout << "Step 4: findMedian()" << '\n';
    auto ans4 = obj.findMedian();
    std::cout << "Got:      " << ans4 << '\n';
    std::cout << "Expected: " << 1.5 << '\n';
    std::cout << "Step 5: addNum(3)" << '\n';
    obj.addNum(3);
    std::cout << "Step 6: findMedian()" << '\n';
    auto ans6 = obj.findMedian();
    std::cout << "Got:      " << ans6 << '\n';
    std::cout << "Expected: " << 2.0 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
