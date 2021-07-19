#include <iostream>
#include <algorithm>
#include <vector>
 
 
struct Solver {
  int n, root;
  std::vector < int > left, right;
  Solver() {
    std::cin >> n >> root;
    --root;
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> left[i] >> right[i];
      --left[i]; --right[i];
    }
  }
public:
  void Solve() {
    int v = root, last = -1;
    bool was = false;
    while(true) {
      if (last != v)
        std::cout << v + 1 << " ";
      int go = left[v];
      int temp = go;
      left[v] = right[v];
      right[v] = last;
      last = v;
      if (go != -1) v = go; else
      if (v == root && was) break;
      was = true;
    }
    std:: cout << '\n';
  }
};
 
 
int main() {
#ifdef Estb_probitie
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
 
  int T;
  std::cin >> T;
  while(T--) {
    Solver solution;
    solution.Solve();
  }
  return 0;
}
