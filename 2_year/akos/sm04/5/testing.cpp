#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

extern "C" void sort_by_abs(void *ptr, size_t count);

int main() {
  {
    std::vector<int16_t> arr = {-4, -2, 0, 1, 3};
    sort_by_abs(&arr[0], arr.size());
    std::cout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << "\n";
    assert((arr == std::vector<int16_t>({0, 1, -2, 3, -4})));
  }

  {
    std::vector<int16_t> arr = {std::numeric_limits<int16_t>::min(), 0, 1, 2};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>(
                       {0, 1, 2, std::numeric_limits<int16_t>::min()})));
  }

  {
    std::vector<int16_t> arr = {std::numeric_limits<int16_t>::min(),
                                std::numeric_limits<int16_t>::max()};
    sort_by_abs(&arr[0], arr.size());
    assert(
        (arr == std::vector<int16_t>({std::numeric_limits<int16_t>::max(),
                                      std::numeric_limits<int16_t>::min()})));
  }

  {
    std::vector<int16_t> arr = {-1, -2, -3, -4, -5, -6};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({-1, -2, -3, -4, -5, -6})));
  }

  {
    std::vector<int16_t> arr = {-1, -6, -2, -4, -3, -5};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({-1, -2, -3, -4, -5, -6})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr = {mn, mx, -1, 2, 100,  -500, mx,
                                mn, 0,  0,  4, -128, mx};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>(
                       {0, 0, -1, 2, 4, 100, -128, -500, mx, mx, mx, mn, mn})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr;
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr;
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr = {mn, 0};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({0, mn})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr = {0, mn};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({0, mn})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr = {mx, 0};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({0, mx})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr = {0, mx};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({0, mx})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr = {mn};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({mn})));
  }

  {
    int16_t mn = std::numeric_limits<int16_t>::min();
    int16_t mx = std::numeric_limits<int16_t>::max();
    std::vector<int16_t> arr = {mx};
    sort_by_abs(&arr[0], arr.size());
    assert((arr == std::vector<int16_t>({mx})));
  }
}
