#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
 
class Solver {
  std::vector < int > in, out, used, visited, comp;
  std::vector < std::vector < int > > g, rg;
  int n, m;
  void visit(int v) {
    used[v] = true;
    for (int to : g[v])
      if (!used[to])
        visit(to);
    visited.push_back(v);
  }
  void rvisit(int v, int col) {
    comp[v] = col;
    used[v] = true;
    for (int to : rg[v])
      if (!used[to])
        rvisit(to, col);
  }
public:
  Solver() {
    std::cin >> n >> m;
    g.resize(n);
    comp.resize(n);
    rg.resize(n);
 
    for (int i = 0; i < m; ++i) {
      int x, y;
      std::cin >> x >> y;
      if (x == y) continue;
      g[x].push_back(y);
      rg[y].push_back(x);
    }
  }
  void Solve() {
    used.resize(n);
    for (int i = 0; i < n; ++i)
      if (!used[i]) {
        visit(i);
      }
    reverse(visited.begin(), visited.end());
    fill(used.begin(), used.end(), false);
    int col = 0;
    for (int v : visited)
      if (!used[v]) {
        rvisit(v, col++);
      }
 
    int isolate = 0;
    in.resize(col);
    out.resize(col);
 
    for (int v = 0; v < n; ++v) {
      for (int to : g[v])
        if (comp[v] != comp[to]) {
          ++in[comp[to]];
          ++out[comp[v]];
        }
    }
    int noIn = 0, noOut = 0;
    for (int v = 0; v < col; ++v) {
      if (!in[v] && !out[v]) ++isolate; else
      if (!in[v]) ++noIn; else
      if (!out[v]) ++noOut;
    }
    if (col == 1) std::cout << "0\n"; else
                  std::cout << std::max(noIn, noOut) + isolate << '\n';
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
