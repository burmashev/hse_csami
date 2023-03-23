#include <iostream>
#include <vector>

struct S {
  struct S *next;
  int m1[12];
  int m2[12];
};

extern "C" int get_ans(S *ptr, int i, int j);

int main() {
  S b = {0,
         {1, 2, -3, 4, 5, -6, 7, 8, 9, 10, 11, 12},
         {12, -11, 10, 9, 8, -7, 6, 5, 4, 3, 2, 1}};
  S a = {&b,
         {1, 0, -1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 2, 0, -3, 0, 4, 0, 5, 0, 6}};
  std::cout << get_ans(&a, 2, 5) << "\n";
}
