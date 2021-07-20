#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
 
class Solver {
  std::vector < std::vector <int> > g, ans;
  std::vector < int > deg, start;
  std::vector < std::pair < int , int > > edge;
  std::vector < bool > used;
  std::vector < int > order;
  int n, m, k;
  void dfs(int v) {
    order.push_back(v);
    while(start[v] < g[v].size()) {
      if (!used[g[v][start[v]]]) break;
      ++start[v];
    }
 
    if (start[v] < g[v].size()) {
      auto edg = edge[g[v][start[v]]];
      int to = edg.first;
      if (edg.first == v) to = edg.second;
      used[g[v][start[v]]] = true;
      ++start[v];
      dfs(to);
    }
  }
 
public:
  void Solve() {
    std::cin >> n >> m;
    start.resize(n, 0);
    deg.resize(n);
    g.resize(n);
 
    for (int i = 0; i < m; ++i) {
      int a, b, s, t;
      std::cin >> a >> b >> s >> t;
      --a; --b;
      if (s != t) {
        g[a].push_back(edge.size());
        g[b].push_back(edge.size());
        edge.emplace_back(a, b);
        ++deg[a];
        ++deg[b];
      }
    }
    used.resize(edge.size());
    for (int i = 0; i < n; ++i)
      if (deg[i] % 2) {
        std::cout << "NIE\n";
        return;
      } else if (start[i] < g[i].size())
        dfs(i);
    std::stack < int > s;
    fill(used.begin(), used.end(), false);
    used.resize(n, false);
    //order = {1, 2, 3, 2, 4 , 5, 6, 2, 3, 1};
    for (int v : order) {
      s.push(v);
      if (used[v]) {
        ans.emplace_back();
        do {
          ans.back().push_back(s.top());
          used[s.top()] = false;
          s.pop();
        } while(!s.empty() && s.top() != v);;
        ans.back().push_back(v);
      }
      used[v] = true;
    }
    std::cout << ans.size() << '\n';
    for (const auto& rows : ans) {
      std::cout << rows.size() - 1 << " ";
      for (const auto& column : rows)
        std::cout << column + 1 << " ";
      std::cout << '\n';
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
