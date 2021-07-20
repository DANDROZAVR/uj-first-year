#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <random>
#include <memory.h>
 
std::mt19937 gen(123);
 
class Solver {
public:
  int n;
  std::vector < std::pair<int , int> > arr;
  void quickSort(int l, int r) {
      if (l >= r) return;
      int mid = gen() % (r - l + 1) + l; //rng
      int val = arr[mid].first;
      int i = l, k = l;
      for (int j = l; j <= r; ++j) {
        if (arr[j].first == val) {
          std::swap(arr[j], arr[k++]);
        } else
        if (arr[j].first < val) {
          std::swap(arr[k], arr[j]);
          std::swap(arr[i++], arr[k++]);
        }
      }
 
      quickSort(l, i - 1);
      quickSort(k, r);
  }
 
  Solver() {
    std::cin >> n;
    arr.reserve(n * 3);
    for (int i = 0; i < n; ++i) {
      int a, b, c, d;
      std::cin >> a >> b >> c;
      arr.emplace_back(a, i);
      arr.emplace_back(b, i);
      arr.emplace_back(c, i);
    }
  }
  void Solve() {
    quickSort(0, (int)(arr.size()) - 1);
    int cnt[n];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < arr.size(); ++i)
      if (!cnt[arr[i].second]) {
        ++cnt[arr[i].second];
        std::cout << arr[i].first << " ";
      }
    std::cout << '\n';
 
    memset(cnt, 0, sizeof(cnt));
    int j = 0;
    int ans = 2e9;
    int haveRows = 0;
    std::pair<int, int> ind;
 
    for (int i = 0; i < arr.size(); ++i) {
      while(j < arr.size() && haveRows < n) {
        if (!cnt[arr[j].second]) ++haveRows;
        ++cnt[arr[j].second];
        ++j;
      }
      if (haveRows < n) break;
      if (ans > arr[j - 1].first - arr[i].first) {
        ans = arr[j - 1].first - arr[i].first;
        ind = {i, j};
      }
      --cnt[arr[i].second];
      if (!cnt[arr[i].second]) --haveRows;
    }
 
    std::cout << ans << '\n';
    memset(cnt, 0, sizeof(cnt));
    for (int i = ind.first; i < ind.second; ++i)
      if (!cnt[arr[i].second])
        cnt[arr[i].second] = arr[i].first;
    for (int i = 0; i < n; ++i)
      std::cout << cnt[i] << " ";
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
