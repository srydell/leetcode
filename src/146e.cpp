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
#include <utility>

using namespace std;
class LRUCache {
  // std::list + unordered_map is the canonical solution but it's
  // * Allocation heavy
  // * Pointer chasing
  // * bad for cache locality
  //
  // So instead I'm implementing a doubly linked list based on indices in a preallocated vector of nodes.

  // Start by introducing what a node is
  struct Node {
    int key = 0;
    int value = 0;

    // Index within m_nodes
    int next = -1;
    int prev = -1;
  };

  vector<Node> m_nodes;
  // {key -> index within m_nodes}
  unordered_map<int, int> m_keyToIndex;

  // Which indices are free to use?
  vector<int> m_free;

  // Head is most recently used
  // Tail is least recently used
  int m_head = -1;
  int m_tail = -1;

  void unlink(int idx) {
    // Want to restore the links to prev/next from this node and then clear the links from this node.

    int prev = m_nodes[idx].prev;
    int next = m_nodes[idx].next;

    if (prev != -1) {
      // m_nodes[prev].next pointed to idx before
      // Need to reset it
      m_nodes[prev].next = next;
    } else {
      // This node didn't have a prev => it was head
      m_head = next;
    }

    if (next != -1) {
      // m_nodes[next].prev pointed to idx before
      m_nodes[next].prev = prev;
    } else {
      // It's tail!
      m_tail = prev;
    }

    // Clear the links
    m_nodes[idx].prev = -1;
    m_nodes[idx].next = -1;
  }

  void pushToFront(int idx) {
    // Want to safely push head further in the list
    // if there is no head/tail, this is both the new head and tail

    // Head has no prev
    m_nodes[idx].prev = -1;

    m_nodes[idx].next = m_head;

    if (m_head != -1) {
      m_nodes[m_head].prev = idx;
    }

    m_head = idx;

    // Nothing within the list?
    if (m_tail == -1) {
      m_tail = idx;
    }
  }

  void moveToFront(int idx) {
    // Already at the front?
    if (idx == m_head) {
      return;
    }

    // Unlink from its current place
    unlink(idx);

    // Push to the front
    pushToFront(idx);
  }

public:
  LRUCache(int capacity) : m_nodes(capacity) {
    // Reserve upfront in order to avoid expensive rehashing later
    m_keyToIndex.reserve(capacity);
    m_free.reserve(capacity);

    // Keep track of which indices are free
    // Initially, all indices are free.
    for (int i = 0; i < capacity; i++) {
      m_free.push_back(i);
    }
  }

  int get(int key) {
    // Start with the easy case,
    // the key doesn't exist
    auto it = m_keyToIndex.find(key);
    if (it == m_keyToIndex.end()) {
      return -1;
    }

    // Need to mark it as the most recently used
    // i.e. move it to the front of the list
    int idx = it->second;
    moveToFront(idx);

    return m_nodes[idx].value;
  }

  void put(int key, int value) {
    // Easy case first, just update a value
    auto it = m_keyToIndex.find(key);
    if (it != m_keyToIndex.end()) {
      int idx = it->second;

      // Update
      m_nodes[idx].value = value;

      // This is now the most recently used
      moveToFront(idx);
      return;
    }

    // This key does not exist.
    // Do we have fresh nodes to use?
    int idx;
    if (!m_free.empty()) {
      idx = m_free.back();
      m_free.pop_back();
    } else {
      // Evict least recently used. I.e. the tail
      idx = m_tail;

      // Remove the old key from the hashmap before overwriting
      m_keyToIndex.erase(m_nodes[idx].key);

      // Remove this node from the linked list
      unlink(idx);
    }

    // Write the new node contents
    m_nodes[idx].key = key;
    m_nodes[idx].value = value;

    pushToFront(idx);

    // Keep track of it
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
