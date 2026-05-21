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
class LRUCache {
public:
  // Some clarifying questions:
  // Should both get and put be O(1)?
  // yes.
  // What should get return on keys that are not in the cache?
  // -1
  // What happens on negative or zero capacity?
  // capacity >= 1
  //
  // Ok. This is basically a fixed size key value map with some special properties when full.
  // Idea: Keep track of the key-value nodes within the cache with a list.
  // The front of the list keeps the most recently used node while the back keeps the least recently used.
  // On eviction, the back of the list is dropped, which is O(1).
  // Next we need a way to get O(1) access to the nodes within get/put so keep a hash map that points into the list
  LRUCache(int capacity) : m_capacity(capacity) {
  }

  int get(int key) {
    // Start with the easy case that there is no key within the structure
    auto node = m_cache.find(key);
    if (node == m_cache.end()) {
      return -1;
    }

    // Now this node exists, so mark it as the most recently used.
    // This can be most easily done in O(1) time by using splice
    m_nodes.splice(m_nodes.begin(), m_nodes, node->second);

    // Return the value
    return node->second->second;
  }

  void put(int key, int value) {
    // Start as always with the easy case of this being within the cache.
    // Then this becomes an update instead of insertion
    auto node = m_cache.find(key);
    if (node != m_cache.end()) {
      // Update the value
      node->second->second = value;

      // Mark it as last recently used in the same way as before
      m_nodes.splice(m_nodes.begin(), m_nodes, node->second);
      return;
    }

    // This key does not exist so we need to check if there is enough capacity to add it
    if (m_nodes.size() == m_capacity) {
      // Evict the least recently used
      int evictedKey = m_nodes.back().first;
      m_nodes.pop_back();
      // Remove it fron the cache
      m_cache.erase(evictedKey);
    }

    // Add it to the list
    m_nodes.push_front({key, value});

    // Keep track of it in the cache
    m_cache[key] = m_nodes.begin();
  }

private:
  int m_capacity;

  // key -> value
  // front: most recently used
  // back: least recently used
  list<pair<int, int>> m_nodes;

  // To get quick access
  // key -> node iterator
  unordered_map<int, decltype(m_nodes)::iterator> m_cache;
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
