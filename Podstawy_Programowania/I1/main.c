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
 
char ansrv[165];
char ans[165];
 
void solve(int p, int q, const char x[165]){
    int n = 0;
    unsigned long long num = 0L;
    while(x[n]){
        if (x[n] <= '9') {
            num = num * p + x[n] - '0';
        } else {
            num = num * p + x[n] - 'A' + 10;
        }
        ++n;
    }
//    printf("%s %s\n", ans, ansrv);
    for (int i = 0; i < 164; ++i) ans[i] = ansrv[i] = 0;
    int otv = 0;
    while(num){
        long long x = num % q;
        if (x < 10)
            ansrv[otv++] = '0' + x; else
            ansrv[otv++] = 'A' + x - 10;
        num /= q;
    }
    if (!otv) ansrv[otv++] = '0';
    for (int i = 0; i < otv; ++i) {
        ans[i] = ansrv[otv - i - 1];
    }
}
 
int main(){
 
 
    #ifdef Estb_probitie
    freopen("C:\\1\\work\\Clion\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Clion\\output.txt", "w", stdout);
    #endif
    int z;
    scanf("%d", &z);
    while(z--) {
        char s[9];
        scanf("%s", &s);
        if (strcmp(s, "CONVERT") == 0){
            char x[165];
            int p, q;
            scanf("%d %d %s", &p, &q, &x);
            solve(p, q, x);
            printf("%s\n", ans);
        } else
        if (s[0] == 'W'){
            int r;
            long long x;
            scanf("%d %lld", &r, &x);
            char otv[r + 1];
            otv[r] = 0;
            for (int i = 0; i + 1 < r; ++i) {
                otv[i] = '0';
            }
            unsigned long long bg = 1;
            bg <<= r;
            --bg;
            bool good = 1;
            if (x > bg / 2 && x > 0) good = 0;
            if (-x - 1 > bg / 2 && x < 0) good = 0;
            if (!good){
                printf("ERROR\n");
                continue;
            }
            if (x < 0) {
                x = bg - abs(x) + 1;
            }
 
            int now = r - 1;
            //exit(0);
            while(now >= 0){
                otv[now] = x % 2 + '0';
                x >>= 1;
                --now;
            }
            printf("%s\n", otv);
        } else{
            char s[66];
            scanf("%s", &s);
            long long ans = 0;
            int r = 0;
            for (int i = 0; s[i]; ++i, ++r) {
                ans = (ans << 1) + s[i] - '0';
            }
 
            unsigned long long bg = 1;
            bg <<= r;
            --bg;
            if (s[0] == '1') {
                ans = -((ans - 1) ^ bg);
            }
            printf("%d\n", ans);
        }
    }
}