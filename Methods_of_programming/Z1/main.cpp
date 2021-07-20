#include <bits/stdc++.h>
 
 
class Solver {
  int rows, col, area;
  std::vector < std::vector < int > > forest;
  std::vector < std::vector < bool > > used;
public:
  explicit Solver() {
    std::cin >> rows >> col >> area;
    forest.resize(rows);
    used.resize(rows);
    for (int i = 0; i < rows; ++i) {
      forest[i].resize(col);
      used[i].resize(col, 0);
      for (int j = 0; j < col; ++j)
        std::cin >> forest[i][j];
    }
  }
 
  bool CanBuild(int maxAge) {
    std::vector < std::pair < int , int > > visit;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < col; ++j)
        if (!used[i][j] && forest[i][j] <= maxAge){
            used[i][j] = true;
            std::queue < std::pair < int , int > > q;
            q.push(std::make_pair(i, j));
            int totalSize = 0;
            const int changeX[4] = {0, 0, 1, -1};
            const int changeY[4] = {1, -1, 0, 0};
            visit.push_back(std::make_pair(i, j));
            while(!q.empty() && totalSize <= area) {
                auto front = q.front();
                q.pop();
                ++totalSize;
                int x = front.first;
                int y = front.second;
                for (int loop = 0; loop < 4; ++loop) {
                  int nx = changeX[loop] + x;
                  int ny = changeY[loop] + y;
                  if (nx < 0 || ny < 0 || nx == rows || ny == col || used[nx][ny] || forest[nx][ny] > maxAge) continue;
                  used[nx][ny] = true;
                  q.push({nx, ny});
                  visit.push_back(std::make_pair(nx, ny));
                }
            }
            while(!q.empty()) q.pop();
            if (totalSize >= area) {
              for (auto now : visit)
                used[now.first][now.second] = false;
                return true;
            }
        }
    for (auto now : visit)
      used[now.first][now.second] = false;
    return false;
  }
 
  int Solve() {
    int l = 1, r = 1e6;
    while(l < r) {
      int mid = (l + r) >> 1;
      if (CanBuild(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
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
    auto result = solution.Solve();
    std::cout << result << '\n';
  }
  return 0;
}
