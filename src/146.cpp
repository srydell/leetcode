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
#include <list>
#include <unordered_map>

using namespace std;
class LRUCache {
  // Front is most recently used
  // Back is least recently used
  std::list<pair<int, int>> m_nodes;

  // key -> iterator into nodes
  unordered_map<int, std::list<pair<int, int>>::iterator> m_access;

  int m_capacity;

public:
  // Typical questions to ask:
  // What should get(key) return on non existing keys?
  // -1
  // Are keys and values both integers?
  // yes
  // What happens if capacity is zero?
  // Typically capacity >= 1, but still good to ask
  //
  // Idea: Keep a list of keys->values such that
  // front is the most recently used
  // back is the least recently used
  // Keep a map of keys to get direct access to a node
  LRUCache(int capacity) : m_capacity(capacity) {
  }

  int get(int key) {
    // I first check if the key actually exist.
    // If it does not, this is a cache miss.
    auto it = m_access.find(key);
    if (it == m_access.end()) {
      return -1;
    }

    // Since the key was accessed, it becomes the most recently used item.
    // The map stores an iterator into the list, so I can move that node to the front in O(1)
    m_nodes.splice(m_nodes.begin(), m_nodes, it->second);

    // Note that the iterator is still valid after the splice
    return it->second->second;
  }

  void put(int key, int value) {
    // First handle the easy case where the key simply exists
    // Then this is an update and not an insertion
    auto it = m_access.find(key);
    if (it != m_access.end()) {
      // Update the value
      it->second->second = value;

      // Since we touched this key, it becomes the most recently used.
      m_nodes.splice(m_nodes.begin(), m_nodes, it->second);
      return;
    }

    // If this is a new key and the cache is already full,
    // evict the least recently used item, which is at the back
    if (m_nodes.size() == m_capacity) {
      int lru_key = m_nodes.back().first;
      m_nodes.pop_back();
      m_access.erase(lru_key);
    }

    // Insert the new key/value pair as the most recently used
    m_nodes.push_front({key, value});

    // Store an iterator to the list node so future access is O(1).
    m_access[key] = m_nodes.begin();
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
