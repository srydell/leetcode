#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  string predictPartyVictory(string senate) {

    int32_t RBans = 0;
    int32_t DBans = 0;
    bool hasBannedThisRound = true;
    while (hasBannedThisRound) {
      hasBannedThisRound = false;
      for (size_t i = 0; i < senate.size(); i++) {
        auto senator = senate[i];
        if (senator == 'R') {
          if (RBans > 0) {
            hasBannedThisRound = true;
            senate[i] = 'x';
            RBans--;
          } else {
            DBans++;
          }
        } else if (senator == 'D') {
          if (DBans > 0) {
            hasBannedThisRound = true;
            senate[i] = 'x';
            DBans--;
          } else {
            RBans++;
          }
        }
      }
    }

    for (auto senator : senate) {
      if (senator == 'R') {
        return "Radiant";
      } else if (senator == 'D') {
        return "Dire";
      }
    }

    // Should never happen
    return "Radiant";
  }
};

int main() {
  Solution solution;

  {
    string senate = "RD";
    auto ans = solution.predictPartyVictory(senate);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: "
              << "Radiant" << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string senate = "RDD";
    auto ans = solution.predictPartyVictory(senate);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: "
              << "Dire" << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
