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
    while(t--){
        int n;
        scanf("%d", &n);
        int a[n], b[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
 
        bool byl = 1;
        for (int i = 0; i < n; ++i) {
            int ind = i, mn = a[i];
            for (int j = i; j < n; ++j)
                if (a[j] < a[ind]){
                    ind = j;
                    mn = a[j];
                }
            int x = a[i];
            a[i] = a[ind];
            a[ind] = x;
        }
        for (int i = 0; i < n; ++i)
            printf("%d ", a[i]);
        printf("\n");
        int st = 0;
        while(st < n && a[st] < 0) ++st;
        byl = 0;
        for (int i = st; i < n && !byl; ++i){
            int now = st;
            for (int j = st; j < n && !byl && now >= 0; ++j) {
                while(now >= 0 && -a[now] < a[i] + a[j]) --now;
                if (now >= 0 && -a[now] == a[i] + a[j]){
                    printf("TAK %d %d %d\n", now, i, j);
                    byl = 1;
                }
            }
        }
        for (int i = st - 1; i >= 0 && !byl; --i){
            int now = st;
            for (int j = i; j >= 0 && !byl && now < n; --j) {
                while(now < n && -a[i] + -a[j] > a[now]) ++now;
                if (now < n && -a[i] + -a[j] == a[now]){
                    printf("TAK %d %d %d\n", j, i, now);
                    byl = 1;
                }
            }
        }
        if (!byl) printf("NIE\n");
    }
}