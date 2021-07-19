#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
 
 
class Solver {
  std::vector < std::vector < int > > g;
  std::vector < long long > sz, ans;
  int *parent;
  int n;
  void calcSz(int v) {
    sz[v] = 1;
    ans[v] = 0;
    for (int to : g[v]) {
      calcSz(to);
      sz[v] += sz[to];
      ans[v] += ans[to] + sz[to];
    }
  }
  void solve(int v) {
    for (int to : g[v]) {
      ans[to] = 0;
      ans[to] = ans[v] - sz[to] + n - sz[to];
      solve(to);
    }
  }
public:
  explicit Solver() {
    std::cin >> n;
    sz.resize(n);
    ans.resize(n);
    parent = new int[n];
    g.resize(n);
    std::pair < int , int > inputEdges[n];
    for (int i = 0; i < n; ++i)
      std::cin >> inputEdges[i].first >> inputEdges[i].second;
    std::queue <int> q;
    q.push(0);
    while(!q.empty()) {
      int i = q.front();
      q.pop();
      int l = inputEdges[i].first, p = inputEdges[i].second;
      --l; --p;
      if (l != -1) {
        g[i].push_back(l);
        q.push(l);
        parent[l] = i;
      }
      if (p != -1) {
        g[parent[i]].push_back(p);
        q.push(p);
        parent[p] = parent[i];
      }
    }
  }
  ~Solver() {delete[] parent;}
  void Solve() {
    calcSz(0);
    solve(0);
    long long maxValue = 0, answer = -1;
    for (int i = 0; i < n; ++i)
      if (ans[i] > maxValue) {
        maxValue = ans[i];
        answer = i;
      }
    std::cout << answer + 1 << '\n';
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
