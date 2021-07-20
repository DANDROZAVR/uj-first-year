#include <stdio.h>
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
 
#define N 10002
#define M 26002
short int kol[N][27];
char s[N][105];
 
int swp(int i, int j){
    for (int k = 0; k < 26; ++k)
        if (kol[i][k] > kol[j][k]) return 0; else
        if (kol[i][k] < kol[j][k]) return 1;
    return 2;
}
int nxt = 0, next[N], last[N], fir[N], Sz[N], sz[N], a[N];
int main(){
 
 
    #ifdef Estb_probitie
    freopen("C:\\1\\work\\Clion\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Clion\\output.txt", "w", stdout);
    #endif
    int z;
    scanf("%d", &z);
    while(z--) {
        int n;
        nxt = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", &s[i]);
            for (int j = 0; j < 26; ++j) {
                kol[i][j] = 0;
            }
            for (int j = 0; s[i][j]; ++j) {
                kol[i][tolower(s[i][j])-'a']++;
            }
        }
        for (int i = 0; i < n; ++i) {
            a[i] = i;
        }
        for (int step = n / 2; step > 0; step /= 2) {
            for (int i = step; i < n; ++i) {
                for (int j = i - step; j >= 0 && swp(a[j], a[j + step]) == 1; j -= step){
                    int tmp = a[j];
                    a[j] = a[j + step];
                    a[j + step] = tmp;
                }
            }
        }
        for (int i = 0; i <= n; ++i) {
            fir[i] = sz[i] = Sz[i] = last[i] = 0;
        }
        int i = 0;
        while(i < n){
            int j = i;
            while(j < n && swp(a[i], a[j]) == 2) ++j;
            int len =  j - i;
            sz[nxt++] = len;
            if (!fir[len]){
                fir[len] = i;
            }
            int ls = last[len];
            next[ls] = i;
            last[len] = i;
            Sz[len]++;
            i = j;
        }
 
        printf("%d\n", nxt);
        for (int I = n; I >= 0; --I){
            int now = fir[I];
            for (int j = 0; j < Sz[I]; ++j){
                printf("%d ", I);
                for (int k = 0; k < I; ++k) {
                    printf("%s ", s[a[k + now]]);
                }
                printf("\n");
                now = next[now];
            }
        }
    }
}