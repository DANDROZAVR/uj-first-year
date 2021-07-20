#include <iostream>
#include <stack>
#include <vector>
#include <random>
 
 
std::mt19937 gen(123);
 
class Solver {
public:
  int n, t;
  std::vector <std::vector <std::pair <int, int>> > g;
  std::vector <long long> dist;
  std::vector <int> order;
 
  Solver() {
    std::cin >> t >> n;
    g.resize(n);
    dist.resize(n);
    for (int i = 1; i < n; ++i) {
      int x, y, w;
      std::cin >> x >> y >> w;
      g[x].push_back({y, w});
      g[y].push_back({x, w});
    }
  }
  void dfs(int v, int pr = -1, long long w = 0) {
    dist[v] = w;
    for (auto to : g[v])
      if (pr != to.first)
        dfs(to.first, v, to.second + w);
  }
  void smart_sort() {
    long long div = 1;
    std::vector <int> all;
    all.reserve(n);
    for (int i = 0; i < n; ++i)
      all.push_back(i);
    for (int k = 0; k < 3; ++k) {
      int cnt[n];
      std::fill(cnt, cnt + n, 0);
      for (int i = 0; i < n; ++i) {
        auto &item = all[i];
        int rem = ((dist[item] / div) % n);
        ++cnt[rem];
      }
      for (int i = 1; i < n; ++i)
        cnt[i] += cnt[i - 1];
      int another[n];
      for (int i = n - 1; i >= 0; --i)
        another[--cnt[(dist[all[i]] / div) % n]] = all[i];
      for (int i = 0; i < n; ++i)
        all[i] = another[i];
      div *= n;
    }
    swap(all, order);
    //return std::move(all);
  }
  void Solve() {
    dfs(0);
    smart_sort();
 
    for (int &i: order)
      if (i >= 1 && i <= t)
        std::cout << dist[i] << " ";
    std::cout << '\n';
    for (int &i: order)
      if (i > t && i <= 2 * t)
        std::cout << dist[i] << " ";
    std::cout << '\n';
 
    int track = 0, home = n - 1;
    long long ans = 0, curTime = -1;
    for (int i = 0; i < t; ++i) {
      while(!(order[track] >= 1 && order[track] <= t)) ++track;
      while(!(order[home] > t && order[home] <= t * 2)) --home;
      curTime = std::max(curTime, dist[order[track]]) + 1;
      ans = std::max(ans, curTime + dist[order[home]]);
      ++track;
      --home;
    }
    std::cout << ans << '\n';
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
