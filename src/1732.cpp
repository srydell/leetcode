#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int largestAltitude(vector<int> &gain) {
    int currentAltitude = 0;
    int maxAltitude = currentAltitude;
    for (size_t i = 0; i < gain.size(); i++) {
      currentAltitude += gain[i];
      maxAltitude = max(maxAltitude, currentAltitude);
    }
    return maxAltitude;
  }
};

int main() {
  Solution solution;

  {
    vector<int> gain = {-5, 1, 5, 0, -7};
    auto ans = solution.largestAltitude(gain);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
  }

  {
    vector<int> gain = {-4, -3, -2, -1, 4, 3, 2};
    auto ans = solution.largestAltitude(gain);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
  }
}
