#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <random>
 
std::mt19937 gen(123);
 
class Solver {
public:
  int n;
  std::vector < int > arr;
  void quickSort(int l, int r) {
      if (l >= r) return;
      int mid = gen() % (r - l + 1) + l; //rng
      int val = arr[mid];
      int i = l, k = l;
      for (int j = l; j <= r; ++j) {
        if (arr[j] == val) {
          std::swap(arr[j], arr[k++]);
        } else
        if (arr[j] < val) {
          std::swap(arr[k], arr[j]);
          std::swap(arr[i++], arr[k++]);
        }
      }
 
      quickSort(l, i - 1);
      quickSort(k, r);
  }
 
  Solver() {
    std::cin >> n;
    arr.reserve(n);
    for (int i = 0; i < n; ++i) {
      int a, b, c, d;
      std::cin >> a >> b >> c;
      arr.push_back(std::min(a, std::min(b, c)));
    }
  }
  void Solve() {
    quickSort(0, n - 1);
    for (int i = 0; i < n; ++i)
      std::cout << arr[i] << " ";
    std::cout << '\n';
  }
};
 
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifdef Estb_probitie
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int z;
  std::cin >> z;
  while(z--) {
    Solver s;
    s.Solve();
  }
}
