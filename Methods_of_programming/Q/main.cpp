#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
 
class Solver {
  std::vector < int > a, b;
  int n, k;
  const int const1 = 10;
  void merge_sort(int l, int r) {
    if (l < r) {
      int mid = (l + r) >> 1;
      merge_sort(l, mid);
      merge_sort(mid + 1, r);
      //ans += bad(l, mid, r);
      for (int i = l; i <= r; ++i)
        b[i] = a[i];
      int l1 = l, l2 = mid + 1, now = l;
      while(now <= r) {
        if (l1 > mid) {
          a[now++] = b[l2];
          l2++;
          continue;
        }
        if (l2 > r) {
          a[now++] = b[l1];
          l1++;
          continue;
        }
        if (b[l1] > b[l2]) {
          a[now++] = b[l1];
          l1++;
        } else {
          a[now++] = b[l2];
          l2++;
        }
      }
    }
  }
public:
  Solver() {
    std::cin >> n >> k;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i)
      std::cin >> a[i];
  }
  void Solve() {
    merge_sort(0, n - 1);
    for (int i = 0; i < n; ++i)
      std::cout << a[i] << " ";
    std::cout << '\n';
  }
};
 
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
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
