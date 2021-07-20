#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
 
class Solver {
  std::vector < std::vector <int> > g;
  std::vector < long long >  in, out;
  std::vector < int > t, edgeTo, used, order;
  long long ans = 0;
  int n, m;
  bool bad = false;
  void queue_sort() {
    std::queue <int> q;
    for (int i = 0; i < n; ++i)
      if (!edgeTo[i])
        q.push(i);
    while(!q.empty()) {
      int v = q.front();
      order.push_back(v);
      q.pop();
      for (int to : g[v]) {
        --edgeTo[to];
        if (!edgeTo[to]) {
          edgeTo[to] = -1;
          q.push(to);
        }
      }
    }
  }
  void go(int v) {
    used[v] = 1;
    for (int to : g[v]) {
      if (!used[to])
        go(to); else
      if (used[to] == 1)
        bad = true;
    }
    order.push_back(v);
    used[v] = 2;
  }
  void dfs_sort() {
    for (int i = 0; i < n; ++i)
      if (!used[i])
        go(i);
    reverse(order.begin(), order.end());
    fill(used.begin(), used.end(), 0);
  }
public:
  void Solve() {
    std::cin >> n >> m;
    g.resize(n);
    t.resize(n);
    edgeTo.resize(n);
    in.resize(n);
    out.resize(n);
    used.resize(n);
    for (int i = 0; i < n; ++i)
      std::cin >> t[i];
    for (int i = 0; i < m; ++i) {
      int x, y;
      std::string trash;
      std::cin >> x >> trash >> y;
      --x; --y;
      g[x].push_back(y);
      edgeTo[y]++;
    }
    dfs_sort();
    if (bad) {
      std::cout << "CYKL\n";
      order = {};
    } else {
      for (int i : order) {
        for (int to : g[i]) {
          in[to] = std::max(in[to], in[i] + t[i]);
        }
      }
      for (int i = order.size() - 1; i >= 0; --i) {
        for (int to : g[order[i]]) {
          out[order[i]] = std::max(out[to] + t[to], out[order[i]]);
        }
        ans = std::max(ans, in[order[i]] + out[order[i]] + t[order[i]]);
      }
      std::cout << "OK " << ans << '\n';
    }
 
    int k;
    std::cin >> k;
    while(k--) {
      int v, dif;
      std::cin >> v >> dif;
      if (order.size() != n) continue;
      --v;
      if (in[v] + out[v] + t[v] + dif > ans)
        std::cout << "NIE " << in[v] + out[v] + t[v] + dif - ans << '\n'; else
        std::cout << "TAK\n";
    }
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
