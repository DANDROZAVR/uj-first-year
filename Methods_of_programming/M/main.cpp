#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
 
class Solver {
  int * distance,*last,* ans;
  std::vector < int > guliverDistance;
  int n, m, start, end;
  std::vector < std::vector < int > > g;
  void calcGuliverWay(std::queue <int> q) {
    while(!q.empty()) {
      int v = q.front();
      q.pop();
      for (int to : g[v]) {
        if (guliverDistance[to] == -1) {
          q.push(to);
          guliverDistance[to] = guliverDistance[v] + 1;
        } else
          guliverDistance[to] = std::min(guliverDistance[v] + 1, guliverDistance[to]);
      }
    }
  }
  void bfs(int start, bool shouldCountAns = true) {
    std::queue <int> q;
    for (int i = 0; i < n; ++i) {
      last[i] = last[i]= -1;
      distance[i] = distance[i] = -1;
    }
    distance[start] = 0;
    if (shouldCountAns) ans[start] = guliverDistance[start];
    q.push(start);
    while(!q.empty()) {
      int v = q.front();
      q.pop();
      if (guliverDistance[v] == 0) continue;
      for (int to : g[v]) {
        if (distance[to] == -1) {
          q.push(to);
          distance[to] = distance[v] + 1;
          last[to] = v;
          if (shouldCountAns) ans[to] = std::min(guliverDistance[to], ans[v]);
        }
        if(shouldCountAns)
        if (distance[to] == distance[v] + 1 && std::min(guliverDistance[to], ans[v]) > ans[to]) {
          last[to] = v;
          ans[to] = std::min(guliverDistance[to], ans[v]);
        }
      }
    }
  }
public:
  ~Solver() {
    if (ans != nullptr)
      delete []ans;
    delete []distance;
    delete []last;
  }
  void Solve() {
    std::cin >> n >> m >> start >> end;
    --start; --end;
    g.resize(n);
    ans = new int[n];
    last = new int[n];
    distance = new int[n];
    guliverDistance.resize(n, -1);
    int k;
    std::cin >> k;
    std::queue <int> q;
    for (int i = 0; i < k; ++i) {
      int x;
      std::cin >> x;
      --x;
      q.push(x);
      guliverDistance[x] = 0;
    }
    for (int i = 0; i < m; ++i) {
      int x, y;
      std::cin >> x >> y;
      --x; --y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    calcGuliverWay(q);
    bfs(start);
 
    int cond = 0;
    int v = end;
    std::vector <int> res;
    if (distance[end] != -1) {
      std::cout << "TAK " << ans[end] << '\n';
      while(v != -1) {
        res.push_back(v);
        int newCond = cond - (guliverDistance[v] == 0);
        v = last[v];
        cond = newCond;
      }
    } else {
      delete[] ans;
      ans = nullptr;
      int distance2[n], last2[n];
      for (int i = 0; i < n; ++i) {
        distance2[i] = distance[i];
        last2[i] = last[i];
      }
      bfs(end, false);
      int min = 2e9, index = -1;
      for (int i = 0; i < n; ++i) {
        if (distance[i] + distance2[i] < min && distance[i] != -1 && distance2[i] != -1) {
          min = distance2[i] + distance[i];
          index = i;
        }
      }
 
      if (index == -1){
        std::cout << "NIE\n";
        return;
      }
      std::cout << "TAK " << 0 << '\n';
      v = last[index];
      while(v != -1) {
        res.push_back(v);
        v = last[v];
      }
      std::reverse(res.begin(), res.end());
      v = index;
      while(v != -1) {
        res.push_back(v);
        v = last2[v];
      }
    }
 
    std::reverse(res.begin(), res.end());
    std::cout << res.size() << " ";
    for (int ver : res)
      std::cout << ver + 1 << " ";
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
