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
        int n;
        scanf("%d", &n);
        int *a = (int*) malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i)
            scanf("%d", (a+i));
        int *ans = (int*) malloc(n * sizeof(int));
 
        int last = 0;
        int *ans2 = (int*) malloc(n * sizeof(int));
        for (int i = 1; ; ++i){
            int now = 0;
            for (int j = 0; j < n && now < i; ++j){
                if ((j == 0 || *(a+j-1) > *(a+j)) && (j + 1 == n || *(a+j+1) > *(a+j))){
                     *(ans2+now) = j;
                     ++now;
                     j += i - 1;
                }
            }
            if (now < i) break;
            for (int j = 0; j < now; ++j)
                *(ans + j) = *(ans2 + j);
            last = now;
        }
        printf("%d\n", last);
        for (int i = 0; i < last; ++i)
            printf("%d ", *(ans + i));
        printf("\n");
        free(ans);
        free(ans2);
        free(a);
    }
}