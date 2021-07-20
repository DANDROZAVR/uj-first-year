#include <iostream>
#include <stack>
#include <vector>
#include <random>
#include <chrono>
 
class Node {
public:
  int sum, active, mx;
  Node() : sum(0), active(0), mx(0){}
  Node(int f, int s, int t) : sum(f), active(s), mx(t) {}
  Node(const Node& another) {
    sum = another.sum;
    active = another.active;
    mx = std::max(mx, another.mx);
  }
  inline Node operator+(const Node &elem) const {
    return {sum + elem.sum, active + elem.active, std::max(mx, elem.mx)};
  }
};
 
class SegTree {
  std::vector <Node> t;
  int leaves;
  int findPositive(int v) {
    if (v >= leaves) return v;
    if (t[v << 1].active)
      return findPositive(v << 1);
    return findPositive(v << 1 | 1);
  }
  Node sum(int v, int tl, int tr, int left, int right) {
    if (left > right) return {0, 0, 0};
    if (tl == left && tr == right) {
      return t[v];
    }
    int mid = (tl + tr) >> 1;
    return sum(v << 1, tl, mid, left, std::min(right, mid)) +
           sum(v << 1 | 1, mid + 1, tr, std::max(mid + 1, left), right);
  }
public:
  SegTree(int n) {
    leaves = 1;
    while(leaves < n)
      leaves <<= 1;
    t.resize(leaves * 2);
  }
  void add(int pos, int val) {
    int v = leaves + pos;
    t[v].active = 1;
    t[v].sum += val;
    t[v].mx += val;
    v >>= 1;
    while(v) {
      t[v] = t[v << 1] + t[v << 1 | 1];
      v >>= 1;
    }
  }
  int del(int pos) {
    int v = leaves + pos;
    if (!t[v].sum) return 0;
    int res = t[v].sum;
    t[v].active = t[v].sum = t[v].mx = 0;
    v >>= 1;
    while(v) {
      t[v] = t[v << 1] + t[v << 1 | 1];
      v >>= 1;
    }
    return res;
  }
  int max(int v, int tl, int tr, int left, int right) {
    if (left > right) return 0;
    if (tl == left && tr == right) return t[v].mx;
    int mid = (tl + tr) >> 1;
    return std::max(max(v << 1, tl, mid, left, std::min(mid, right)),
                    max(v << 1 | 1, mid + 1, tr, std::max(mid + 1, left), right));
  }
  inline Node sum(int left,int right) { return sum(1, 0, leaves - 1, left, right);}
  inline int max(int left, int right) { return max(1, 0, leaves - 1, left, right);}
  std::pair <int, int> next(int pos) {
    int v = pos + leaves;
    while(v) {
      if (v % 2 == 0) {
        if (t[v >> 1].active > t[v].active) {
          v >>= 1;
          break;
        }
      }
      v >>= 1;
    }
    if (!v) return {-1, -1};
    int ans = findPositive(v << 1 | 1);
    return {ans - leaves, t[ans].sum};
  }
};
class Solver {
 
public:
  int n, q;
  Solver() {
    std::cin >> n >> q;
  }
  void Solve() {
    SegTree t(n);
    for (int i = 0; i < q; ++i) {
      std::string command;
      std::cin >> command;
      int first, second;
      std::cin >> first;
      if (command != "NXT" && command != "DEL") {
        std::cin >> second;
      }
      if (command == "INS")
        t.add(first, second);
      if (command == "DEL") {
        int res = t.del(first);
        if (!res)
          std::cout << "ERROR\n"; else
          std::cout << res << '\n';
      }
      if (command == "SUM")
        std::cout << t.sum(first, second).sum << '\n';
      if (command == "AVE") {
        Node res = t.sum(first, second);
        if (!res.active)
          std::cout << "ERROR\n"; else
          std::cout << round((double)(res.sum) / res.active) << '\n';
      }
      if (command == "NXT") {
        auto res = t.next(first);
        if (res.first == -1)
          std::cout << "ERROR\n"; else
          std::cout << res.first << " " << res.second << '\n';
      }
      if (command == "MAX")
        std::cout << t.max(first, second) << '\n';
    }
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
