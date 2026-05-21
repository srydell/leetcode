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
// I start by asking some clarifying questions.
// Is capacity always >0?
// Yes.
// Do both get and put have to be O(1)?
// Yes.
// Are both key/value ints?
// Yes.
// What should I return on non existing keys in get?
// -1
//
// Ok. Then I need a fast way of getting the value and a fast way of adding in new values.
// I also need a way to be fast about evicting least used keys as the capacity is reached.
// To add new keys fast I would use a list and to find the key/value pairs in O(1) time I would use a hash map.
// Lets keep a list of all the nodes within the structure and a map that points to specific iterators within that list.
// Let the head of the list be the most recently used and the tail of the list be the least recently used.
// This way, evicting the least recently used is simply popping the tail.
class LRUCache {
  // {key, value}
  // head is the most recently used
  // tail is the least recently used
  list<pair<int, int>> m_nodes;

  // {key -> node in m_nodes}
  unordered_map<int, decltype(m_nodes)::iterator> m_cache;

  // NOTE: >0
  int m_capacity;

public:
  LRUCache(int capacity) : m_capacity(capacity) {
  }

  int get(int key) {
    // Start off with the easy case that this key does not exist.
    auto it = m_cache.find(key);
    if (it == m_cache.end()) {
      return -1;
    }

    // Mark it as the most recently used. I.e. moving it to the head.
    // The easiest way to do that with a std::list is with splice.
    m_nodes.splice(m_nodes.begin(), m_nodes, it->second);

    // Return the value
    // NOTE: The iterator is still valid after splice.
    // This keeps the m_cache map working
    return it->second->second;
  }

  void put(int key, int value) {
    // Start with the easy case that this is a cache hit.
    // Then this is an update instead of an insertion.
    auto it = m_cache.find(key);
    if (it != m_cache.end()) {
      // Update the value
      it->second->second = value;

      // Mark as most recently used
      m_nodes.splice(m_nodes.begin(), m_nodes, it->second);

      return;
    }

    // This is a new value
    // Do we have capacity to add it?
    if (m_nodes.size() == m_capacity) {
      // Pop the least recenty used
      auto evicted_key = m_nodes.back().first;
      m_cache.erase(evicted_key);
      m_nodes.pop_back();
    }

    // Push to front since this is now the most recently used
    m_nodes.push_front({key, value});
    // Keep track of the key value in the cache
    m_cache[key] = m_nodes.begin();
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
