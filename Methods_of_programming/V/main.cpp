#include <iostream>
#include <stack>
#include <vector>
#include <random>
#include <chrono>
 
 
class MinMaxHeap {
  std::vector <int> a;
  int sz;
public:
  MinMaxHeap(){sz = 2;}
  void clear() {
    a.clear();
    sz = 2;
  }
  bool isEmpty() const {
    return sz == 2;
  }
  void add(int elem) {
    int v = sz++;
    if (v >= a.size()) {
      a.resize(sz * 2);
    }
    a[v] = elem;
    while(true) {
      int parentIndex = (v >> 1);
      int leftParent = (parentIndex % 2 ? parentIndex - 1 : parentIndex);
      int rightParent = leftParent + 1;
      if (v & 1) {
        // right child
        if (a[v - 1] > a[v]) {
          std::swap(a[v - 1], a[v]);
          --v;
        }
      } else {
        //left child
        if (v + 1 < sz && a[v] > a[v + 1]) {
          std::swap(a[v], a[v + 1]);
          ++v;
        }
      }
      if (v <= 3) break;
      if (a[leftParent] > a[v]) {
        std::swap(a[v], a[leftParent]);
        v = leftParent;
        continue;
      }
      if (a[rightParent] < a[v]) {
        std::swap(a[v], a[rightParent]);
        v = rightParent;
        continue;
      }
      break;
    }
  }
 
  int getMin() const {if (sz == 2) return -1; return a[2];}
  int getMax() const {if (sz == 2) return -1; if (sz == 3) return a[2]; return a[3];}
  int popMin() {
    auto res = a[2];
    a[2] = a[--sz];
    int v = 2;
    while(v + 1 < sz) {
      if (a[v] > a[v + 1])
        std::swap(a[v], a[v + 1]);
      int fIndex = (v << 1);
      if (fIndex >= sz) break;
      int sIndex = ((v + 1) << 1);
      if (sIndex >= sz || a[fIndex] <= a[sIndex]) {
        if (a[v] <= a[fIndex]) break;
        std::swap(a[v], a[fIndex]);
        v = fIndex;
        continue;
      }
      if (sIndex >= sz || a[v] <= a[sIndex]) break;
      std::swap(a[v], a[sIndex]);
      v = sIndex;
    }
    return res;
  }
  int getSize() const { return sz - 2; }
  int popMax() {
    int v = 3;
    if (getSize() == 1) --v;
    auto res = a[v];
    a[v] = a[--sz];
    while(v < sz) {
      if (a[v] < a[v - 1])
        std::swap(a[v], a[v - 1]);
      int fIndex = (v << 1) - 1;
      if (fIndex >= sz) break;
      int sIndex = (v << 1) | 1;
      if (sIndex >= sz || a[fIndex] >= a[sIndex]) {
        if (a[v] >= a[fIndex]) break;
        std::swap(a[v], a[fIndex]);
        v = fIndex;
        continue;
      }
      if (sIndex >= sz || a[v] >= a[sIndex]) break;
      std::swap(a[v], a[sIndex]);
      v = sIndex;
    }
    return res;
  }
};
 
class Solver {
  int n;
  MinMaxHeap heap1, heap2;
public:
  Solver() {std::cin >> n;}
  void Solve() {
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
      int k;
      std::cin >> k;
      for (int j = 0; j < k; ++j) {
        int val;
        std::cin >> val;
        if (heap1.getSize() <= 2*n + 4 && heap2.isEmpty())
          heap1.add(val); else {
            if (heap2.isEmpty()) {
              for (int i2 = 0; i2 < n + 1; ++i2)
                heap2.add(heap1.popMax());
            }
            if (heap1.getMax() > val) {
              heap1.popMax();
              heap1.add(val);
            } else
            if (heap2.getMin() < val) {
              heap2.popMin();
              heap2.add(val);
            }
          }
      }
      if (heap2.isEmpty())
        ans += heap1.popMax() - heap1.popMin(); else
        ans += heap2.popMax() - heap1.popMin();
    }
    std::cout << ans << '\n';
  }
};
 
std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
 
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
