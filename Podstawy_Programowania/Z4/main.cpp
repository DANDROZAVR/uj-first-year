#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
 
#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
 
#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
 
const int M = 1000;
int bin_pow(int n, int m){
    if (!m) return 1;
    if (m == 1) return n;
    if (m % 2) return (n * bin_pow(n, m - 1)) % M;
    return bin_pow((n * n) % M, m >> 1);
}
 
int main(int argc, char *argv[]) {
    //FILE *inp;
    //FILE *out;
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Clion\\input.txt", "r",  stdin);
    freopen("C:\\1\\work\\Clion\\output.txt", "w", stdout);
#endif
 
    int z;
    scanf("%d", &z);
    while(z--){
        int n, m, t, u, k;
        scanf("%d %d %d %d %d ", &n, &m, &t, &u, &k);
        int kol[m];
        int sm = (m / 32) + (m % 32 > 0);
        int s[n][sm];
        memset(kol, 0, sizeof(kol));
        for (int i = 0; i < n; ++i){
            char q[m + 1];
            memset(q, 0, sizeof(q));
            scanf("%s", &q);
            int tim = 0, now = 0, x = 0;
            for (int j = 0; q[j]; ++j){
                x = (x << 1) + q[j] - '0';
                ++tim;
                //printf("%d\n", x);
                if (tim == 32){
                    s[i][now++] = x;
                    x = 0;
                    tim = 0;
                }
            }
            if (tim){
                s[i][now++] = x;
            }
        }
        int all = 0;
        int byl[n];
        memset(byl, 0, sizeof(byl));
        for (int i = 0; i < n; ++i) {
            int good = byl[i];
            for (int j = i + 1; j < n; ++j) {
                int cm = 0;
                for (int k = 0; k < sm; ++k)
                    cm += __builtin_popcount(s[i][k] & s[j][k]);
                //printf("%d %d %d\n", i, j, cm);
                if (cm >= t) ++good, ++byl[j];
            }
            all += (good >= u);
        }
 
        int ans = bin_pow(all, k);
        printf("%d %.3d\n", all, ans);
    }
 
 
}