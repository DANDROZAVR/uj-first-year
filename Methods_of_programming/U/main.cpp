#include <iostream>
#include <stack>
#include <vector>
#include <random>
 
 
class Heap {
  std::vector <std::pair <int, int>> a; //sort by first value
  int sz;
public:
  Heap(){sz = 1;}
  void push(std::pair <int, int> elem) {
    int v = sz++;
    if (v >= a.size()) {
      a.resize(sz * 2);
    }
    a[v] = elem;
    while(v > 1) {
      if (a[v >> 1].first < a[v].first) break;
      std::swap(a[v >> 1], a[v]);
      v >>= 1;
    }
  }
  std::pair <int, int> pop() {
    auto res = a[1];
    a[1] = a[--sz];
    int v = 1;
    while((v << 1) < sz) {
      if ((v << 1) + 1 < sz) {
        std::pair <int, int>& elem1 = a[v << 1];
        std::pair <int, int>& elem2 = a[(v << 1) + 1];
        if (elem1.first < elem2.first) {
          if (a[v].first < elem1.first) break;
          std::swap(a[v], elem1);
          v <<= 1;
        } else {
          if (a[v].first < elem2.first) break;
          std::swap(a[v], elem2);
          v = (v << 1) + 1;
        }
      } else {
        std::pair <int, int>& elem1 = a[v << 1];
        if (elem1.first < a[v].first)
          std::swap(a[v], elem1);
        v <<= 1;
      }
    }
    return res;
  }
  void clear() {
    a.clear();
    sz = 1;
  }
  bool isEmpty() const {
    return sz == 1;
  }
};
 
class Solver {
  int n;
  std::vector <int> a, b, c, d;
public:
  Solver() {
    std::cin >> n;
    a.resize(n);
    b.resize(n);
    c.resize(n);
    d.resize(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i] >> b[i] >> c[i] >> d[i];
      --a[i]; --b[i]; --c[i]; --d[i];
    }
  }
  void Solve() {
    int row[n];
    std::vector <std::vector <std::pair <int, int>>> rectan;
    rectan.resize(n);
    for (int i = 0; i < n; ++i) {
      rectan[a[i]].emplace_back(c[i], i);
    }
    Heap heap;
    for (int i = 0; i < n; ++i) {
      for (auto& item : rectan[i])
        heap.push(item);
      rectan[i].clear();
      if (!heap.isEmpty()) {
        auto elem = heap.pop();
        if (elem.first < i) {
          std::cout << "ERROR\n";
          return;
        }
        row[elem.second] = i;
      }
    }
    if (!heap.isEmpty()) {
      std::cout << "ERROR\n";
      return;
    }
    for (int i = 0; i < n; ++i) {
      rectan[b[i]].emplace_back(d[i], i);
    }
    int column[n];
    for (int i = 0; i < n; ++i) {
      for (auto& item : rectan[i])
        heap.push(item);
      if (!heap.isEmpty()) {
        auto elem = heap.pop();
        if (elem.first < i) {
          std::cout << "ERROR\n";
          return;
        }
        column[elem.second] = i;
      }
    }
    if (!heap.isEmpty()) {
      std::cout << "ERROR\n";
      return;
    }
    for (int i = 0; i < n; ++i)
      std::cout << row[i] + 1 << " " << column[i] + 1 << '\n';
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
