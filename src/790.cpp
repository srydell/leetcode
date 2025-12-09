#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
  int numTilings(int n) {
    if (n <= 2) {
      return n;
    }

    std::vector<int> tilings(n + 1, 0);
    tilings[0] = 1;
    tilings[1] = 1;
    tilings[2] = 2;
    const int mod = 1000000007;
    for (int i = 3; i <= n; i++) {
      tilings[i] = (2LL * tilings[i - 1] % mod + tilings[i - 3]) % mod;
    }

    return tilings[n];
  }
};

int main() {
  Solution solution;

  {
    int n = 3;
    int expected = 5;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.numTilings(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int n = 1;
    int expected = 1;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.numTilings(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
