#include <bits/stdc++.h>
std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
 
 
 
class Solver {
  int n;
  const unsigned long long mul[6][5] = {{99999989, 999983 , 99991, 12301, 44664869},
                                        {99991, 999983 , 99999989, 12301, 44664869},
                                        {44664869, 999983 , 99999989, 12301, 12301},
                                        {99999989, 99991 , 99991, 999983, 44664869},
                                        {99999989, 999983 , 99991, 44664869, 12301},
                                        {44664869, 99999989 , 12301, 12301, 99991},
  };
  long long randNext(unsigned long long n) {
    int i = n % 6;
    long long res = ((n ^ mul[i][4]) * ((n << 12) * mul[i][0] + (n << 4) * mul[i][1]+ (n << 6) * mul[i][2] + (n ^ mul[i][3]) + (n >> 5))) / 2;
    return res;
  }
public:
  Solver() {
    std::cin >> n;
  }
  void Solve() {
    std::vector < long long > all;
    //mp.reserve(2e6);
//    for (int i = 0; i <= 1000; ++i)
//      std::cout << +randNext(i) - randNext(i + 1)<< '\n';
    for (int i = 0; i < n; ++i) {
      std::string s;
      std::cin >> s;
      std::stack< long long > st;
      st.push(0);
      for (char j : s) {
        if (j == '(') {
          st.push(0);
        } else {
          auto res = randNext(st.top());
          st.pop();
          st.top() += res;
        }
      }
      all.push_back(st.top());
      //while(true) continue;
    }
    sort(all.begin(), all.end());
    std::cout << std::unique(all.begin(), all.end()) - all.begin() << '\n';
  }
};
 
int main() {
#ifdef Estb_probitie
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
//  int n = 1;
//  std::cout<<n<<'\n'<<1<<'\n\;
//  int clc = 0;
//  int sz = 2e6;
//  for (int i = 0; i < sz; ++i) {
//    char c;
//    if (!clc) c = '('; else {
//      const int cnst = (i < 100000 ? 5 : 2);
//      int x = gen() % cnst;
//      if (x) c = '('; else c = ')';
//    }
//    std::cout << c;
//    if (c == '(') ++clc; else --clc;
//  }
//  exit(0);
  int z;
  std::cin >> z;
  while(z--) {
    Solver solve;
    solve.Solve();
  }
 
}
