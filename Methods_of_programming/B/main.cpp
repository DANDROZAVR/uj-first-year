#include <bits/stdc++.h>
 
 
class Solver {
  int cyclonesNumber;
  std::vector < std::pair < int , int > > cyclones, vectorDirection;
public:
  explicit Solver() {
    std::cin >> cyclonesNumber;
    cyclones.resize(cyclonesNumber);
    vectorDirection.resize(cyclonesNumber);
    for (int i = 0; i < cyclonesNumber; ++i) {
      std::cin >> cyclones[i].first >> cyclones[i].second;
      std::cin >> vectorDirection[i].first >> vectorDirection[i].second;
    }
  }
 
  long double MakeSquare(long double time, long double prevAns = 0) {
    long double minY, minX, maxX, maxY;
    for (int i = 0; i < cyclonesNumber; ++i) {
      std::pair < long double, long double > newCyclone = {cyclones[i].first + vectorDirection[i].first * time,
                                                           cyclones[i].second + vectorDirection[i].second * time};
      if (!i) {
        minX = maxX = newCyclone.first;
        minY = maxY = newCyclone.second;
        continue;
      }
 
      minY = std::min(minY, (long double)newCyclone.second);
      minX = std::min(minX, (long double)newCyclone.first);
      maxY = std::max(maxY, (long double)newCyclone.second);
      maxX = std::max(maxX, (long double)newCyclone.first);
      if (prevAns > 0 && std::max(maxX - minX, maxY - minY) > prevAns) return std::max(maxX - minX, maxY - minY);
    }
    return std::max(maxX - minX, maxY - minY);
  }
 
  std::pair < long double, long double > Solve() {
    int llog = 0, rlog = 26;
//    while(llog + 2 < rlog) {
//      int step = (rlog - llog) / 3;
//      int mid1 = llog + step, mid2 = rlog - step;
//      long double res1 = MakeSquare(1 << mid1);
//      long double res2 = MakeSquare(1 << mid2, res1);
//      if (res1 < res2) rlog = mid2; else llog = mid1;
//    }
    long double l = (1 << llog) - 1, r = (1ll << (rlog + 1)) - 1;
    //std::cerr << l << " " << r << '\n';
    while(r - l > 0.000000001) {
      long double step = (r - l) / 3;
      long double mid1 = l + step, mid2 = r - step;
      //std::cerr << mid1 << " " << mid2 << " " << MakeSquare(mid1) << " " << MakeSquare(mid2) << std::endl;
      long double res1 = MakeSquare(mid1);
      long double res2 = MakeSquare(mid2, res1);
      if (res1 < res2) r = mid2; else l = mid1;
    }
    return std::make_pair(MakeSquare(l), l);
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
    auto result = solution.Solve();
    std::cout << std::fixed << std::setprecision(10) << result.first << " " << result.second << '\n';
  }
  return 0;
}
