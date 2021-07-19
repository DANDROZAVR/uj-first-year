#include <bits/stdc++.h>
#include <vector>
 
 
class Solver {
  const int p1 = 29, m1 = (int)(1e9) + 107, N = 2001;
  std::vector < int > pw;
  std::vector < int > calcHash(std::string s) const {
    std::vector < int > res;
    int h = 0;
    for (int i = 0; i  < s.size(); ++i) {
      h += s[i] * pw[i];
      res.push_back(h);
    }
    return res;
  }
  void calcPower(int k) {
    pw[0] = 1;
    for (int i = 1; i <= k; ++i)
      pw[i] = (1ll * pw[i - 1] * p1) % m1;
  }
  int getHash(std::vector < int > &h, int from, int to) {
    if (from > to) return 0;
    if (!from) return h[to];
    auto res = h[to] - h[from - 1];
    if (res < 0) res += m1;
    return res;
  }
  bool equals(std::vector < int > &f, std::vector < int > &s, int from, int to) {
    if (from > to) return true;
    auto get1 = getHash(f, from, to);
    auto get2 = getHash(s, from, to);
    return get1 == get2;
  }
public:
  void Solve() {
    int n, k;
    std::vector < std::vector < int > > hash;
    std::cin >> n >> k;
    pw.resize(k+ 2);
    calcPower(k);
    for (int i = 0; i < n; ++i) {
      std::string s;
      std::cin >> s;
      hash.push_back(calcHash(s));
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
      int dif0, dif1, dif2;
      dif0 = dif1 = dif2 = 0;
      std::string q;
      std::cin >> q;
      auto itemHash = calcHash(q);
      for (int i = 0; i < n; ++i) {
        if (itemHash.back() == hash[i].back()) {
          ++dif0;
          continue;
        }
        int l = 0, r = k - 1;
        while (l < r) {
          int mid = (l + r) >> 1;
          if (equals(hash[i], itemHash, 0, mid)) l = mid + 1; else r = mid;
        }
        int l2 = l + 1, r2 = k - 1;
        if (equals(hash[i], itemHash, l2, k - 1)) {
          ++dif1;
          continue;
        }
       // std::cout << equals(hash[i], itemHash, 4, 4);exit(0);
        while(l2 < r2) {
          int mid = (l2 + r2) >> 1;
          if (equals(hash[i], itemHash, l2, mid)) l2 = mid + 1; else r2 = mid;
        }
        if (equals(hash[i], itemHash, l2 + 1, k - 1))
          ++dif2;
      }
      std::cout << dif0 << " " << dif1 << " " << dif2 << '\n';
      if (dif0 + dif1 + dif2 == 0) {
        hash.push_back(itemHash);
        ++n;
      }
    }
  }
};
 
int main() {
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
