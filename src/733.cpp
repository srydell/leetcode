// Flood Fill
// Difficulty: Easy
//
// You are given an image represented by an m x n grid of integers image, where image[i][j]
// represents the pixel value of the image. You are also given three integers sr, sc, and
// color. Your task is to perform a flood fill on the image starting from the pixel
// image[sr][sc]. To perform a flood fill: Begin with the starting pixel and change its
// color to color. Perform the same process for each pixel that is directly adjacent
// (pixels that share a side with the original pixel, either horizontally or vertically)
// and shares the same color as the starting pixel. Keep repeating this process by checking
// neighboring pixels of the updated pixels and modifying their color if it matches the
// original color of the starting pixel. The process stops when there are no more adjacent
// pixels of the original color to update. Return the modified image after performing the
// flood fill.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color) {
    int startColor = image[sr][sc];
    if (startColor == color) {
      return image;
    }
    image[sr][sc] = color;

    queue<pair<int, int>> indices;
    indices.push({sr, sc});

    while (!indices.empty()) {
      auto [r, c] = indices.front();
      indices.pop();

      if (r - 1 >= 0 && image[r - 1][c] == startColor) {
        image[r - 1][c] = color;
        indices.push({r - 1, c});
      }

      if (r + 1 < image.size() && image[r + 1][c] == startColor) {
        image[r + 1][c] = color;
        indices.push({r + 1, c});
      }

      if (c - 1 >= 0 && image[r][c - 1] == startColor) {
        image[r][c - 1] = color;
        indices.push({r, c - 1});
      }

      if (c + 1 < image[0].size() && image[r][c + 1] == startColor) {
        image[r][c + 1] = color;
        indices.push({r, c + 1});
      }
    }
    return image;
  }
};

int main() {
  Solution solution;

  {
    // From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color. Note the bottom corner is not colored 2, because it is not horizontally or vertically connected to the starting pixel.
    vector<vector<int>> image = vector<vector<int>>{{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    int sr = 1;
    int sc = 1;
    int color = 2;
    vector<vector<int>> expected = vector<vector<int>>{{2, 2, 2}, {2, 2, 0}, {2, 0, 1}};
    std::cout << "Input:    " << str(image) << ", " << sr << ", " << sc << ", " << color << '\n';
    auto ans = solution.floodFill(image, sr, sc, color);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The starting pixel is already colored with 0, which is the same as the target color. Therefore, no changes are made to the image.
    vector<vector<int>> image = vector<vector<int>>{{0, 0, 0}, {0, 0, 0}};
    int sr = 0;
    int sc = 0;
    int color = 0;
    vector<vector<int>> expected = vector<vector<int>>{{0, 0, 0}, {0, 0, 0}};
    std::cout << "Input:    " << str(image) << ", " << sr << ", " << sc << ", " << color << '\n';
    auto ans = solution.floodFill(image, sr, sc, color);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
