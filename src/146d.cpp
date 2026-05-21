// LRU Cache
// Difficulty: Medium
//
// Design a data structure that follows the constraints of a Least Recently Used (LRU)
// cache. Implement the LRUCache class: LRUCache(int capacity) Initialize the LRU cache
// with positive size capacity. int get(int key) Return the value of the key if the key
// exists, otherwise return -1. void put(int key, int value) Update the value of the key if
// the key exists. Otherwise, add the key-value pair to the cache. If the number of keys
// exceeds the capacity from this operation, evict the least recently used key. The
// functions get and put must each run in O(1) average time complexity.

#include "helpers.hpp"

#include <iostream>
#include <unordered_map>

// This is after a discussion on cache friendliness, allocation etc.
using namespace std;
class LRUCache {
  // Instead of using std::list nodes allocated all over the heap,
  // I keep the linked list pointers directly inside a contiguous array.
  //
  // This improves locality and avoids per node allocations.
  struct Node {
    int key = 0;
    int value = 0;

    // Indices within m_nodes instead of iterators
    int prev = -1;
    int next = -1;

    // Good for debugging, can remove later
    bool used = false;
  };

  // All nodes stored contiguously
  vector<Node> m_nodes;

  // {key -> node index}
  unordered_map<int, int> m_keyToIndex;

  // Reusable unused node indices
  vector<int> m_free;

  int m_capacity;

  // Doubly linked list:
  //
  // head = most recently used
  // tail = least recently used
  int m_head;
  int m_tail;

  void unlink(int idx) {
    int prev = m_nodes[idx].prev;
    int next = m_nodes[idx].next;

    // Connect previous node to the next node
    if (prev != -1) {
      m_nodes[prev].next = next;
    } else {
      // No previous means this node was the head
      m_head = next;
    }

    // Connect next node to the previous node
    if (next != -1) {
      m_nodes[next].prev = prev;
    } else {
      // No next means this node was the tail
      m_tail = prev;
    }

    // Clear the links
    m_nodes[idx].prev = -1;
    m_nodes[idx].next = -1;
  }

  void pushFront(int idx) {
    // New head has no previous node
    m_nodes[idx].prev = -1;

    // Point at the current head.
    m_nodes[idx].next = m_head;

    // If the list was non-empty,
    // update the old heap to point back
    if (m_head != -1) {
      m_nodes[m_head].prev = idx;
    }

    // Update head.
    m_head = idx;

    // If the list was empty,
    // this node it also the tail.
    if (m_tail == -1) {
      m_tail = idx;
    }
  }

  void moveToFront(int idx) {
    // Already most recently used?
    if (idx == m_head) {
      return;
    }

    // Remove from its current position
    unlink(idx);

    // Reinsert at the front.
    pushFront(idx);
  }

public:
  LRUCache(int capacity) : m_capacity(capacity), m_nodes(capacity), m_head(-1), m_tail(-1) {
    // Reserve upfront to avoid rehashing latency spikes later.
    m_keyToIndex.reserve(capacity);

    // Build a freelist of available node indices
    //
    // At the beginning all nodes are unused.
    for (int i = 0; i < capacity; i++) {
      m_free.push_back(i);
    }
  }

  int get(int key) {
    // Easy case first: cache miss.
    auto it = m_keyToIndex.find(key);
    if (it == m_keyToIndex.end()) {
      return -1;
    }

    int idx = it->second;

    // Accessing a node makes it most recently used
    moveToFront(idx);

    return m_nodes[idx].value;
  }

  void put(int key, int value) {
    // First handle the easy case:
    // this key already exists.
    auto it = m_keyToIndex.find(key);

    if (it != m_keyToIndex.end()) {
      int idx = it->second;

      // Update the value
      m_nodes[idx].value = value;

      // Since it was touched,
      // it becomes the most recently used
      moveToFront(idx);

      return;
    }

    int idx;

    // If there is remaining capacity,
    // take a fresh unused node.
    if (!m_free.empty()) {
      idx = m_free.back();
      m_free.pop_back();
    } else {
      // Otherwise evict the least recently used node.
      //
      // The tail is always the least recently used.
      idx = m_tail;

      // Remove the old key from the hashmap before overwriting.
      m_keyToIndex.erase(m_nodes[idx].key);

      // Remove this node from the linked list.
      unlink(idx);
    }

    // Write the new node contents.
    m_nodes[idx].key = key;
    m_nodes[idx].value = value;
    m_nodes[idx].used = true;

    // Insert as most recently used.
    pushFront(idx);

    // Keep track of where this key lives.
    m_keyToIndex[key] = idx;
  }
};

int main() {
  {
    std::cout << "Example 1" << '\n';
    // LRUCache lRUCache = new LRUCache(2); lRUCache.put(1, 1); // cache is {1=1} lRUCache.put(2, 2); // cache is {1=1, 2=2} lRUCache.get(1); // return 1 lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3} lRUCache.get(2); // returns -1 (not found) lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3} lRUCache.get(1); // return -1 (not found) lRUCache.get(3); // return 3 lRUCache.get(4); // return 4
    std::cout << "Step 1: LRUCache(2)" << '\n';
    LRUCache obj{2};
    std::cout << "Step 2: put(1, 1)" << '\n';
    obj.put(1, 1);
    std::cout << "Step 3: put(2, 2)" << '\n';
    obj.put(2, 2);
    std::cout << "Step 4: get(1)" << '\n';
    auto ans4 = obj.get(1);
    std::cout << "Got:      " << ans4 << '\n';
    std::cout << "Expected: " << 1 << '\n';
    std::cout << "Step 5: put(3, 3)" << '\n';
    obj.put(3, 3);
    std::cout << "Step 6: get(2)" << '\n';
    auto ans6 = obj.get(2);
    std::cout << "Got:      " << ans6 << '\n';
    std::cout << "Expected: " << -1 << '\n';
    std::cout << "Step 7: put(4, 4)" << '\n';
    obj.put(4, 4);
    std::cout << "Step 8: get(1)" << '\n';
    auto ans8 = obj.get(1);
    std::cout << "Got:      " << ans8 << '\n';
    std::cout << "Expected: " << -1 << '\n';
    std::cout << "Step 9: get(3)" << '\n';
    auto ans9 = obj.get(3);
    std::cout << "Got:      " << ans9 << '\n';
    std::cout << "Expected: " << 3 << '\n';
    std::cout << "Step 10: get(4)" << '\n';
    auto ans10 = obj.get(4);
    std::cout << "Got:      " << ans10 << '\n';
    std::cout << "Expected: " << 4 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
