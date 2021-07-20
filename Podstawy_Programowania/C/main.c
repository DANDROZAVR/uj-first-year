#include <stdio.h>
#include <stdbool.h>
#include <math.h>
 
 
 
int main() {
    //freopen("input.txt", "r", stdin);
    //FILE *fil = freopen("output.txt", "w", stdout);
    //FILE *file = fopen("output.txt", "w");
 
    int z;
    scanf("%d", &z);
    while(z--){
        int n;
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            if (i) a[i] += a[i - 1];
        }
        int q;
        scanf("%d", &q);
        while(q--){
            int x;
            scanf("%d", &x);
            int l = 0, r = n;
            while(l < r){
                int mid = (l + r) >> 1;
                if (x >= a[mid])
                    l = mid + 1; else r = mid;
            }
            printf("%d\n", l);
        }
    }
}