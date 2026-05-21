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

using namespace std;
// So how could this solution be improved?
// Well, the std::list & unordered_map solution is asymptotically O(1) but the constant factors are quite large.
// std::list allocates for each new node added and it also allocates extra meta data for each node. In my previous solution
// I did not even reserve the map size in order to avoid expensive rehashing later on.
// So the current solution has high allocations, lots of pointer chasing, and poor cache locality.
// It's also a bit sad that get is a modifying function due to potential order changes within the node list.
// That would make it awkward to move to a multiple thread type solution.
//
// A better solution would address the nodes structure to have a doubly linked list preallocated within a static vector
// the size of the capacity. Note that this at least initially trades size for speed.
class LRUCache {
  // Start by defining the new node structure
  struct Node {
    int key = 0;
    int value = 0;

    // Indices within the node vector
    int prev = -1;
    int next = -1;
  };

  vector<Node> m_nodes;

  // Need to keep track of the number of free nodes within m_nodes
  // Note that capacity is reached when m_free.empty() is true.
  vector<int> m_free;

  // {key -> node index within m_nodes}
  unordered_map<int, int> m_cache;

  // Need to keep track of head/tail
  // head is the most recently used
  int m_head = -1;
  // tail is the least recently used
  int m_tail = -1;

  void unlink(int idx) {
    // NOTE: Assumes idx is within m_nodes and exists
    // Should remove the links prev/next from this node

    int prev = m_nodes[idx].prev;
    int next = m_nodes[idx].next;

    if (prev != -1) {
      // Set prev next to next
      m_nodes[prev].next = next;
    } else {
      // No prev => this node is the head
      m_head = next;
    }

    if (next != -1) {
      // Set next prev to prev
      m_nodes[next].prev = prev;
    } else {
      // No next => This node it the tail
      m_tail = prev;
    }

    // Unset links
    m_nodes[idx].prev = -1;
    m_nodes[idx].next = -1;
  }

  void pushToFront(int idx) {
    if (idx == m_head) {
      return;
    }

    m_nodes[idx].next = m_head;
    m_nodes[idx].prev = -1;

    if (m_head != -1) {
      // Reset heads prev link
      m_nodes[m_head].prev = idx;
    }

    m_head = idx;

    if (m_tail == -1) {
      // If list completely empty, node is both head and tail
      m_tail = idx;
    }
  }

  void moveToFront(int idx) {
    // NOTE: Assumes idx is within m_nodes and exists
    // Should unlink the node from within the structure
    // and push it to the front

    if (m_head == idx) {
      // Done!
      return;
    }

    unlink(idx);

    pushToFront(idx);
  }

public:
  LRUCache(int capacity) : m_nodes(capacity) {
    m_cache.reserve(capacity);

    // Stock the free indices
    for (int i = 0; i < capacity; i++) {
      m_free.push_back(i);
    }
  }

  int get(int key) {
    // Start with the same as before, a cache miss
    auto it = m_cache.find(key);
    if (it == m_cache.end()) {
      return -1;
    }

    int idx = it->second;
    // Need to mark it as the most recently used.
    moveToFront(idx);

    return m_nodes[idx].value;
  }

  void put(int key, int value) {
    // Start with the easy case of a cache miss.
    // Then this is an update rather than an insertion
    auto it = m_cache.find(key);
    if (it != m_cache.end()) {
      int idx = it->second;
      // Update the value
      m_nodes[idx].value = value;

      // Mark as most recently used
      moveToFront(idx);
      return;
    }

    // Do we have the capacity within the free indices?
    int idx;
    if (!m_free.empty()) {
      idx = m_free.back();
      m_free.pop_back();
    } else {
      // The cache is full,
      // evict the tail
      idx = m_tail;
      int evicted_key = m_nodes[m_tail].key;
      m_cache.erase(evicted_key);
      unlink(m_tail);
    }

    // Update the key/value
    m_nodes[idx].key = key;
    m_nodes[idx].value = value;

    // Mark as most recently used
    pushToFront(idx);

    m_cache[key] = idx;
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
