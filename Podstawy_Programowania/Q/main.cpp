#include <bits/stdc++.h>
#define y1 Y1
using namespace std;
const int X[4] = {0, 0, 1, -1};
const int Y[4] = {1, -1, 0, 0};
const int N = 41;
 
int a[N][N], x1, y1, x2, y2, n, m;
bool byl[N][N], done;
vector < pair < int , int > > vis;
 
void solve(int x, int y, int mv = 4, bool fl = 0){
    byl[x][y] = 1;
    //cout << x << " " << y << " " << mv << " " << fl << endl;
    vis.push_back({x, y});
    if (x == x2 && y == y2){
        cout << "TAK " << vis.size() << endl;
        for (int i = 0; i < vis.size(); ++i){
            if (i) cout << ", ";
            cout << vis[i].first + 1 << " " << vis[i].second + 1;
        }
        cout << '\n';
        vis.clear();
        done = 1;
        return;
    }
    bool enter = 0;
    for (int i = 0; i < 4; ++i){
        if (mv != 4 && i != mv) continue;
        int nx = X[i] + x;
        int ny = Y[i] + y;
        if (nx < 0 || ny < 0 || nx == n || ny == m || byl[nx][ny]) continue;
        if (a[nx][ny] == 1 || (a[nx][ny] == 2 && fl)) continue;
        bool nfl = fl;
        if (a[nx][ny] == 2) nfl = 1;
        enter = 1;
        solve(nx, ny, i, nfl);
        if (done) return;
    }
    if (!enter && mv != 4){
        for (int i = 0; i < 4; ++i){
            int nx = X[i] + x;
            int ny = Y[i] + y;
            if (nx < 0 || ny < 0 || nx == n || ny == m || byl[nx][ny]) continue;
            if (a[nx][ny] == 1 || (a[nx][ny] == 2 && fl)) continue;
            bool nfl = fl;
            if (a[nx][ny] == 2) nfl = 1;
            enter = 1;
            solve(nx, ny, i, nfl);
            if (done) return;
        }
    }
    byl[x][y] = 0;
    vis.pop_back();
}
 
int main(){
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
#endif
    int z;
    cin >> z;
    while(z--){
        done = 0;
        cin >> n >> m;
        cin >> x1 >> y1 >> x2 >> y2;
        --x1, --y1, --x2, --y2;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> a[i][j];
        solve(x1, y1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                byl[i][j] = 0;
        if (!done) cout << "NIE\n";
    }
}