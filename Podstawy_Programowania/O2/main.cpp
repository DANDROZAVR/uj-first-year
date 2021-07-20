#include <bits/stdc++.h>
using namespace std;
 
#define _ << " " <<
#define pb push_back
 
int nwd(int a, int b){
    if (a > b) swap(a, b);
    //cout << a _ b << endl;
    if (!a) return b;
    int k = 0;
    if (!(a & 1) && !(b & 1)) return (nwd(a >> 1, b >> 1) << 1);
    if (a & 1 && !(b & 1)) return nwd(a, b >> 1);
    if (!(a & 1) && b & 1) return nwd(a >> 1, b);
    return nwd((b - a) >> 1, a);
}
 
int main() {
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
        int a, b;
        cin >> a >> b;
        cout << nwd(a, b) << '\n';
    }
    return 0;
}