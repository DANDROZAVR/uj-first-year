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
 
 
int main(int argc, char *argv[]) {
    //FILE *inp;
    //FILE *out;
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Clion\\input.txt", "r",  stdin);
    freopen("C:\\1\\work\\Clion\\output.txt", "w", stdout);
#endif
    int z;
    scanf("%d", &z);
    while(z--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int **a = malloc(n * sizeof(int*));
        for (int i = 0; i < n; ++i){
            *(a + i) = malloc(m * sizeof(int));
            for (int j = 0; j < m; ++j) {
                scanf("%d", *(a + i) + j);
                //if (*(*(a + i) + j) == 1000) *(*(a + i) + j) = 0;
            }
        }
        int x, y;
        scanf("%d %d", &x, &y);
        int **b = malloc(y * sizeof(int *));
        for (int j = 0; j < y; ++j)
            *(b + j) = malloc(x * sizeof(int));
 
        for (int j = 0; j < x; ++j)
            for (int i = 0; i < y; ++i) {
                scanf("%d", *(b + i) + j);
                //if (*(*(b + i) + j) == 1000) *(*(b + i) + j) = 0;
            }
        if (m != x){
            printf("ERROR\n");
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < y; ++j) {
                    int ans = 0;
                    int *f = *(a + i);
                    int *s = (*b) + j;
                    for (int k = 0; k < m; ++k) {
                        ans += *f * *(*(b + j) + k);
                        f++;
                        s++;
                    }
                    ans %= 1000;
                    printf("%.3d ", ans);
                }
                printf("\n");
            }
        }
        for (int i = 0; i < n; ++i)
            free(*(a + i));
        for (int i = 0; i < y; ++i)
            free(*(b + i));
        free(b);
        free(a);
    }
}