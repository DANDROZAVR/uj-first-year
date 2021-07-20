#include <bits/stdc++.h>
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
const int N = 1111111;
bool lp[N];
 
void prim(){
    lp[0] = 1;
    lp[1] = 1;
    for (int i = 2; i < N; ++i)
        if (!lp[i]) {
            if (1ll * i * i < N)
                for (int j = i * i; j < N; j += i)
                    lp[j] = 1;
        }
}
ll x;
vector < int > v;
bool solve(int n, vector < bool > &used, vector < int > ind){
    if (n == ind.size()){
        ll dr = 0;
        for (int i : ind)
            dr = dr * 10 + v[i];
        //cout << abs(dr) << endl;
        if (abs(dr - x) % 9) return false;
        int licz = abs(dr - x) / 9;
        if (licz < N && !lp[licz]) {
            cout << "TAK " << dr << '\n';
            return true;
        }
        return false;
    }
    for (int i = 0; i < n; ++i)
        if (!used[i]){
            used[i] = true;
            ind.pb(i);
            if (solve(n, used, ind)) return true;
            ind.pop_back();
            used[i] = false;
        }
    return false;
}
 
int main(){
    #ifdef Estb_probitie
        freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
        freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
    #endif
    prim();
    int z;
    cin >> z;
    while(z--){
        cin >> x;
        v.clear();
        ll X = x;
        while(x){
            v.pb(x % 10);
            x /= 10;
        }
        x = X;
        reverse(v.begin(), v.end());
        vector < bool > vc(v.size(), false);
        vector < int > emp;
        if (!solve(v.size(), vc, emp)) cout << "NIE\n";
    }
}