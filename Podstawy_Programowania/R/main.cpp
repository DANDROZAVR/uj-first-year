#include <bits/stdc++.h>
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
int n, s, ans;
const int N = 301;
pair < int , int > ind[N], now[N];
int a[N][N];
int str[N], col[N], diag1[N], diag2[N], used;
void solve(int wier, int sused){
    if (sused == s || wier == n){
        int bad = 0;
        for (int i = 0; i < n; ++i)
            if (!str[i]){
                for (int j = 0; j < n; ++j)
                    if (!col[j] && !diag1[i + j] && !diag2[i - j + n]){
                        ++bad;
                        if (bad >= ans) break;
                    }
            }
        if (bad < ans){
            used = sused;
            ans = bad;
            for (int i = 0; i < sused; ++i)
                ind[i] = now[i];
        }
        return;
    }
    for (int i = wier; i < n; ++i)
        if (!str[i]){
            bool byl = 0;
            for (int j = 0; j < n; ++j)
                if (!col[j] && !a[i][j]){
                    byl = 1;
                    now[sused] = {i, j};
                    str[i] = col[j] = 1;
                    diag1[i + j]++;
                    diag2[i - j + n]++;
                    solve(i + 1, sused + 1);
                    if (!ans) return;
                    str[i] = col[j] = 0;
                    diag1[i + j]--;
                    diag2[i - j + n]--;
                }
        }
}
 
int main(){
    #ifdef Estb_probitie
        freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
        freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int z;
    cin >> z;
    while(z--){
        cin >> n >> s;
        for (int i = 0; i <= 2 * n; ++i)
            str[i] = col[i] = diag1[i] = diag2[i] = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> a[i][j];
        ans = n * n;
        used = 0;
        solve(0, 0);
        cout << (!ans ? "TAK" : "NIE");
        if (ans) cout << " " << ans;
        cout << '\n';
        for (int i = 0; i < used; ++i){
            cout << ind[i].first + 1 _ ind[i].second + 1 << '\n';
        }
    }
 
}