#include <iostream>
#include <time.h>
#include <complex>
#include <vector>
 
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
 
const int X[4] = {0, 0, 1, -1};
const int Y[4] = {1, -1, 0, 0};
const int N = (int)(1e8) + 1;
 
bool Primesqr[10001], Prime[N];
const int sqrn = 10000, cache = 31950;
bool num[cache + 1];
#define TIME (1.0 * clock()) / CLOCKS_PER_SEC
 
void prec(){
    //cout << TIME << endl;
    vector < int > primes;
    Primesqr[0] = Primesqr[1] = true;
    for (int i = 2; i * i <= sqrn; ++i)
        if (!Primesqr[i])
            for (int j = i * i; j <= sqrn; j += i)
                Primesqr[j] = true;
    for (int i = 0; i <= sqrn; ++i)
        if (!Primesqr[i]) {
            primes.pb(i);
            Prime[i] = true;
        }
    vector < int > dodatPrimes;
    fill(num, num + cache, 1);
    for (int i = sqrn + 1; i < N; i += cache) {
        for (int j = 0; j < primes.size(); ++j) {
            int h = i % primes[j];
            int k = h > 0 ? primes[j] - h : 0;
            for (; k < cache; k += primes[j])
                num[k] = false;
        }
        for (int j = 0; j < cache; ++j)
            if (num[j]  && j + i < N) {
                Prime[j + i] = true;
            } else num[j] = true;
    }
}
 
int main(int argc, char* argv[]){
    #ifdef Estb_probitie
        freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
        freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
    #endif
    prec();
    int z;
    cin >> z;
    while(z--){
        int a;
        cin >> a;
        cout << Prime[a] << '\n';
    }
}