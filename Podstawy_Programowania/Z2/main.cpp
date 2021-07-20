#include <stdio.h>
#include <math.h>
#include <stdbool.h>
 
 
const int N = 3e5 + 1;
 
#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
 
#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
 
int main(){
 
    #ifdef Estb_probitie
        freopen("C:\\1\\work\\Clion\\input.txt", "r", stdin);
        freopen("C:\\1\\work\\Clion\\output.txt", "w", stdout);
    #endif
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int r[n];
        for (int i = 0; i < n; ++i)
            scanf("%d", &r[i]);
        int now = n - 1;
        bool good = 1;
        int mn[n];
        mn[0] = r[0];
        for (int i = 1; i < n; ++i)
            mn[i] = min(mn[i - 1], r[i]);
        for (int i = 0; i < m; ++i){
            int x;
            scanf("%d", &x);
            while(now >= 0 && mn[now] < x) --now;
            if (now < 0){
                good = 0;
            } else
            --now;
        }
        if (!good){
            printf("0\n");
        } else
            printf("%d\n", now + 2);
    }
}