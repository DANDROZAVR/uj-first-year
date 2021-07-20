#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
 
 
 
#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
 
#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
 
#define N 1000001
 
char odd[N / 2][13], even[N / 2][13];
 
int cmp(const void *a, const void *b){
    return strcmp((char*)a, (char*)b);
}
 
int ans(char a[N / 2][13], int n){
    char best[13];
    strcpy(best, a[0]);
    int now = 1, mx = 1, ind = 0;
    for (int i = 1; i < n; ++i) {
        int x = strcmp(best, a[i]);
        if (x == 0) ++now; else {
            --now;
            if (now == 0){
                strcpy(best, a[i]);
                now = 1;
                ind = i;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += !strcmp(a[i], best);
    }
    if (ans > n / 2) return ind;
    return -1;
}
 
int main(){
 
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Clion\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Clion\\output.txt", "w", stdout);
#endif
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d\n", &n);
        for (int i = 0; i < n; ++i){
            if (i % 2 == 0)
                scanf("%s", odd[i >> 1]);
            else
                scanf("%s", even[i >> 1]);
        }
        int s = ans(even, n / 2), f = ans(odd, n / 2);
        if (f != -1 && s != -1 && strcmp(even[s], odd[f]) != 0)
            printf("TAK %s %s\n", odd[f], even[s]); else
        if (f == -1 && s == -1)
            printf("NIE\n"); else
        if (s == -1)
            printf("JEDNA %s\n", odd[f]); else
            printf("JEDNA %s\n", even[s]);
    }
 
}