#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define pb push_back
 
 
 
bool good(int x){
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return 0;
    return 1;
}
 
int main() {
    //freopen("input.txt", "r", stdin);
    //FILE *fil = freopen("output.txt", "w", stdout);
 
    int q;
    scanf("%d", &q);
    while(q--){
        int x;
        scanf("%d", &x);
        if (good(x))
            printf("%d jest pierwsza\n", x); else
            printf("%d jest zlozona\n", x);
    }
 
}