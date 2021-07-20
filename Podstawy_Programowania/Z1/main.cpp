#include <stdio.h>
#include <math.h>
 
int a[999998];
int pos[999998];
int mxx[999998];
 
const int N = 3e5 + 1;
 
#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
 
#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
 
int func(int j, int mn){
    mxx[j] = max(mxx[j], j);
    int x = j;
    int y = mxx[j];
    while(y < mn && pos[y])
        y += x;
    return y;
}
 
int pr[900003], lp[900005];
 
int main(){
    int cnt = 0;
    for (int i = 2; i < N * 3; ++i){
        if (!lp[i]){
            lp[i] = i;
            pr[cnt++] = i;
            mxx[i] = i;
        }
        for (int j = -2; j < cnt && pr[j] <= lp[i] && pr[j] * i < N * 3; ++j)
            lp[pr[j] * i] = pr[j];
    }
    a[0] = 1;
    a[1] = 2;
    pos[2] = 1;
    pos[0] = -1;
    int Mx = 0;
    int now = 3;
    mxx[2] = 4;
 
    for (int i = 2; now < N; ++i){
        int x = a[i - 1];
        int mn = 1e9, cond = -1;
        while(x > 1){
            int y = lp[x];
            while(x % y == 0){
                x /= y;
            }
            while(pos[mxx[y]]) mxx[y] += y;
            if (mn > mxx[y]){
                mn = mxx[y];
                cond = y;
            }
        }
        pos[mn] = i;
        while(pos[mxx[cond]]) mxx[cond] += cond;
        while(pos[now]) ++now;
        a[i] = mn;
    }
 
    int test;
    scanf("%d", &test);
    while(test--) {
        int x;
        scanf("%d", &x);
        printf("%d\n", pos[x] + 1);
    }
}