#include <bits/stdc++.h>
 
 
class Solver {
  int rooms;
  int persons;
  std::vector < int > teams;
public:
  explicit Solver() {
    std::cin >> rooms >> persons;
    teams.resize(rooms);
    for (int i = 0; i < rooms; ++i)
      std::cin >> teams[i];
  }
 
  bool enoughPeople(int teamsPerPerson) {
    int result = 0;
    for (int i = 0; i < rooms; ++i) {
      int need = teams[i] / teamsPerPerson;
      if (need * teamsPerPerson < teams[i]) ++need;
      result += need;
    }
    return (result <= persons);
  }
 
  int Solve() {
    int l = 1, r = (int)(2e9);
    while(l < r) {
      int mid = (l + r) >> 1;
      if (enoughPeople(mid)) r = mid; else l = mid + 1;
    }
    return l;
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
    std::cout << solution.Solve() << '\n';
  }
  return 0;
}
