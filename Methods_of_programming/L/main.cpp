#include <iostream>
#include <queue>
#include <vector>
 
class Solver {
  std::vector < std::vector <int> > g;
  std::vector < std::vector < std::pair < int , std::pair <int , int> > > >task;
  std::vector < int > dpEven, dpOdd;
  int n, m, k;
  void bfs(int start) {
    fill(dpEven.begin(), dpEven.end(), -1);
    fill(dpOdd.begin(), dpOdd.end(), -1);
    dpEven[start] = 0;
    std::queue < std::pair < int, bool> > q;
    q.push({start, 1});
    while(!q.empty()) {
      int v = q.front().first;
      bool even = q.front().second;
      q.pop();
      for (int to : g[v]) {
        if (even) {
          if (dpOdd[to] == -1) {
            q.push({to, !even});
            dpOdd[to] = dpEven[v] + 1;
          } else
            dpOdd[to] = std::min(dpEven[v] + 1, dpOdd[to]);
        } else {
          if (dpEven[to] == -1) {
            q.push({to, !even});
            dpEven[to] = dpOdd[v] + 1;
          } else
            dpEven[to] = std::min(dpOdd[v] + 1, dpEven[to]);
        }
      }
    }
  }
public:
  void Solve() {
    std::cin >> n >> m >> k;
    g.resize(n);
    dpEven.resize(n);
    dpOdd.resize(n);
    task.resize(n);
    for (int i = 0; i < m; ++i) {
      int a, b;
      std::cin >> a >> b;
      --a; --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    bool ans[k];
    for (int i = 0; i < k; ++i) {
      int a, b, len;
      std::cin >> a >> b >> len;
      --a; --b;
      if (a > b) std::swap(a, b);
      task[a].push_back({b, {len, i}});
    }
    for (int i = 0; i < n; ++i)
      if (!task[i].empty()) {
        bfs(i);
        for (std::pair < int , std::pair < int , int > > item : task[i]) {
          int len = item.second.first;
          int ind = item.second.second;
          int end = item.first;
          if (len % 2) {
            if (dpOdd[end] <= len && dpOdd[end] != -1)
              ans[ind] = true; else
              ans[ind] = false;
          } else {
            if (dpEven[end] <= len && dpEven[end] != -1)
              ans[ind] = true; else
              ans[ind] = false;
          }
        }
    }
    for (int i = 0; i < k; ++i)
      std::cout << (ans[i] ? "TAK" : "NIE") << '\n';
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
