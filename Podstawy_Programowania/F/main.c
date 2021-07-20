#include <stdio.h>
#include <stdbool.h>
#include <math.h>
 
 
 
int main() {
    //freopen("input.txt", "r", stdin);
    //FILE *fil = freopen("output.txt", "w", stdout);
    //FILE *file = fopen("output.txt", "w");
 
    int q;
    scanf("%d", &q);
    char ans[2501][55];
    while(q--){
        char s[51];
        scanf("%s", &s);
        int n = 0;
        bool good = 0;
        while(s[n] != 0) ++n;
 
        int cnt = 0;
        for (int i = 0; i < n; ++i){
            int now = 0;
            for (int j = i; j < n; ++j){
                if (s[j] == '(') ++now; else --now;
                if (now < 0) break;
                if (now == 0){
                    for (int k = 0; k < i; ++k)
                        ans[cnt][k] = s[k];
                    ans[cnt][i] = '[';
                    for (int k = i; k <= j; ++k)
                        ans[cnt][k + 1] = s[k];
                    ans[cnt][j + 2] = ']';
                    for (int k = j + 1; k < n; ++k)
                        ans[cnt][k + 2] = s[k];
                    ans[cnt][n + 2] = 0;
                    ++cnt;
                }
                if (now == 0 && i == 0 && j == n - 1) good = 1;
            }
        }
        if (!good)
            printf("NIE\n"); else
            printf("TAK\n");
        printf("%d\n", cnt);
        for (int i = 0; i < cnt; ++i) {
            printf("%s\n", ans[i]);
        }
 
    }
 
}