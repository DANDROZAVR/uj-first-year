#include <iostream>
#include <stack>
#include <vector>
#include <random>
 
 
std::mt19937 gen(123);
 
class Solver {
public:
  int n, k;
  std::vector <int> arr;
  void median(int &x1, int &x2, int &x3, int &x4, int &x5) {
    bool changed = true;
    while(changed) {
      changed = false;
      if (x1 > x2) {
        changed = true;
        std::swap(x1, x2);
      }
      if (x2 > x3) {
        changed = true;
        std::swap(x2, x3);
      }
      if (x3 > x4) {
        changed = true;
        std::swap(x3, x4);
      }
      if (x4 > x5) {
        changed = true;
        std::swap(x4, x5);
      }
    }
    //return x3;
  }
  void insert_sort(int l, int r) {
    if (l >= r) return;
    bool changed = true;
    while(changed) {
      changed = false;
      for (int i = l; i < r; ++i)
        if (arr[i] > arr[i + 1]) {
          changed = true;
          std::swap(arr[i], arr[i + 1]);
        }
    }
  }
 
  int knumber(int l, int r, int k) {
    if (l + 5 >= r)  {
      insert_sort(l, r);
      return arr[l + k - 1];
    }
 
    const int cntDiv = (r - l + 1) / 5;
 
    for (int i = 0; i < cntDiv; ++i)
      median(arr[i], arr[i + cntDiv], arr[i + cntDiv * 2], arr[i + cntDiv * 3], arr[i + cntDiv * 4]);
    int val = knumber(cntDiv * 2 + l, cntDiv * 3 - 1 + l, cntDiv / 2 + 1);
    int i = l, p = l;
    for (int j = l; j <= r; ++j) {
      if (arr[j] == val) {
        std::swap(arr[j], arr[p++]);
      } else
      if (arr[j] < val) {
        std::swap(arr[p], arr[j]);
        std::swap(arr[i++], arr[p++]);
      }
    }
    if (i - l >= k)
      return knumber(l, i - 1, k);
    if (p - l >= k)
      return val;
    return knumber(p, r, k - (p - l));
  }
 
  Solver() {
    std::cin >> n >> k;
    arr.resize(n);
    for (int i = 0; i < n; ++i)
      std::cin >> arr[i];
  }
  void Solve() {
//    for (int i = 0; i < n; ++i)
//      std::cout << knumber(0, n - 1, i + 1) << " ";
//    std::cout << std::endl;
    std::cout << knumber(0, n - 1, k) << '\n';
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
