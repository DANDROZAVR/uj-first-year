#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define pb push_back
 
const int N = 1e7 + 5;
int lp[10000004];
int pr[1000000];
int pref[10000001];
 
int main() {
    int cnt = 0;
    for (int i = 2; i < N; ++i){
        if (!lp[i]){
            lp[i] = i;
            pr[cnt++] = i;
            pref[i] = 1;
        }
        for (int j = 0; j < cnt && pr[j] <= lp[i] && i * pr[j] < N; ++j)
            lp[pr[j] * i] = pr[j];
    }
    for (int i = 2; i < N; ++i)
        pref[i] += pref[i - 1];
    lp[1] = 1;
    int q;
    scanf("%d", &q);
    while(q--){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d %d %d\n", pref[b] - pref[a - 1], lp[a], lp[b]);
 
    }
    //fclose(fil);
}