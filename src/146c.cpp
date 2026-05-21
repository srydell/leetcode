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

// Questions:
// Both of get/put needs to be O(1)?
// Yes.
// Are both keys and values integers?
// Yes.
// What should get return on non existing keys?
// -1
//
// What happens if capacity is negative or zero?
// It's >=1.
//
// It sounds to me like a fixed size map with special rules for eviction when full.
// If both get and put needs to be O(1), there needs to be eviction at O(1) as well.
// Lets start simple by introducing a list of key value pairs where the front of the
// list is the most recently used key, and the back of the list is the least recently used key.
// This way, popping the least recently used is definitely O(1).
// Then to make finding a random key O(1) we just keep a hash map mapping to an iterator within our list.
using namespace std;
class LRUCache {
  int m_capacity;

  // Front is the most recently used key
  // Back is the least recently used key
  // {key, value}
  list<pair<int, int>> m_nodes;

  // To make finding nodes O(1)
  // {key -> node iterator}
  unordered_map<int, decltype(m_nodes)::iterator> m_cache;

public:
  LRUCache(int capacity) : m_capacity(capacity) {
  }

  int get(int key) {
    // Start with the simple case that this key does not exist
    auto node = m_cache.find(key);
    if (node == m_cache.end()) {
      return -1;
    }

    // Mark this as the most recently used.
    // With a list, we can just splice on the node on the front of the list.
    m_nodes.splice(m_nodes.begin(), m_nodes, node->second);

    // Return the value of this node.
    return node->second->second;
  }

  void put(int key, int value) {
    // Start with this key existing. Then this is an update instead of an insertion.
    auto node = m_cache.find(key);
    if (node != m_cache.end()) {
      // Update it
      node->second->second = value;
      // Mark as most recently used
      m_nodes.splice(m_nodes.begin(), m_nodes, node->second);
      // To find it later.
      m_cache[key] = m_nodes.begin();
      return;
    }

    // This node does not exist within the map
    // Is the capacity full?
    if (m_nodes.size() == m_capacity) {
      // The one to evict
      auto evicted_key = m_nodes.back().first;
      m_cache.erase(evicted_key);
      m_nodes.pop_back();
    }

    // Now we are free to add it to our node list
    m_nodes.push_front({key, value});
    m_cache[key] = m_nodes.begin();
  }
};

// Follow up questions:
// What are the drawbacks of this type of solution?
//
// Well, even though it's asymptotically O(1), the constants and latency profile are not great. std::list gives O(1) movement, but it does so with heap-allocated nodes, pointer chasing, poor spatial locality, and extra memory overhead. The hash map also adds allocation, possible rehashing, and average-case rather than guaranteed O(1). Also, get is mutating (moving node to front), so this design is awkward under concurrency. So it's a clean algorithmic solution, but not necessarily the best production low-latency cache.
//

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
