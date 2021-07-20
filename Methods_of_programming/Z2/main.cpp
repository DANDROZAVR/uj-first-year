#include <bits/stdc++.h>
 
 
class Solver {
  std::vector < std::vector < int > > g;
  int *parent, *lvl;
  int n;
  int dfs(int colours, int v = 0) {
    int sum = (int)(g[v].size()) - colours;
    for (int to : g[v]) {
      sum += dfs(colours, to);
    }
    sum = std::max(sum, 0);
    return sum;
  }
public:
  explicit Solver() {
    std::cin >> n;
    parent = new int[n];
    lvl = new int[n];
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
  ~Solver() {delete[] parent; delete[] lvl;}
  int Solve() {
    int left = 1, right = n;
    while(left < right) {
      int mid = (left + right) >> 1;
      if (!dfs(mid)) right = mid; else left = mid + 1;
    }
    return left;
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
    auto res = solution.Solve();
    std::cout << res << '\n';
  }
  return 0;
}
