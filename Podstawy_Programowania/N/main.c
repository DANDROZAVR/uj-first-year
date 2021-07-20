#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
 
const int M = 1000;
struct pair {
    int x, y;
};
 
int cmp(int l, int r){
    int a = r - l;
    int dr = abs(a);
    dr += !dr;
    a /= dr;
    a *= -1;
    return a;
}
 
int cmp2(int l, int r){
    int a = r - l;
    int dr = abs(a);
    dr += !dr;
    a /= dr;
    return a;
}
 
int less(const void *p, const void *q){
    int l = *(const int *)p;
    int r = *(const int *)q;
    return cmp(l, r);
}
int lesPair(const void *p, const void *q){
    struct pair l = *(const struct pair *)p;
    struct pair r = *(const struct pair *)q;
    int val1 = cmp(l.x, r.x);
    int val2 = cmp(l.y, r.y);
    int ans[3] = {val1, val2, val1};
    return ans[val1 + 1];
}
int lesPairObr(const void *p, const void *q){
    struct pair l = *(const struct pair *)p;
    struct pair r = *(const struct pair *)q;
    int val1 = cmp(l.x, r.x);
    int val2 = cmp(l.y, r.y);
    int ans[3] = {val2, val1, val2};
    return ans[val2 + 1];
}
 
int gre(const void *p, const void *q){
    int l = *(const int *)p;
    int r = *(const int *)q;
    return cmp2(l, r);
}
int ty2(const void *p, const void *q){
    int l = *(const int *)p;
    int r = *(const int *)q;
    int val1 = cmp(abs(l), abs(r));
    int val2 = cmp(l, r);
    int ans[3] = {val1, val2, val1};
    return ans[val1 + 1];
}
int ty3(const void *p, const void *q){
    int l = *(const int *)p;
    int r = *(const int *)q;
    int val1 = cmp2(abs(l), abs(r));
    int val2 = cmp2(l, r);
    int ans[3] = {val1, val2, val1};
    return ans[val1 + 1];
}
struct person
{
    char name[16];
    int salary;
};
int t8(const void *p, const void *q){
    struct person l = *(const struct person *)p;
    struct person r = *(const struct person *)q;
    int val1 = cmp(l.salary, r.salary);
    int val2 = strcmp(l.name, r.name);
    int ans[3] = {val1, val2, val1};
    return ans[val1 + 1];
}
int t9(const void *p, const void *q){
    struct person l = *(const struct person *)p;
    struct person r = *(const struct person *)q;
    int val1 = cmp2(l.salary, r.salary);
    int val2 = strcmp(l.name, r.name) * -1;
    int ans[3] = {val1, val2, val1};
    return ans[val1 + 1];
}
int n, d;
void solve3(){
    int a[n];
    for (int i = 0; i < n; ++i){
        scanf("%d", &a[i]);
    }
    int (*func[6])(const void *, const void *);
    func[0] = less;
    func[1] = gre;
    func[2] = ty2;
    func[3] = ty3;
 
    qsort(a, n, sizeof(a[0]), func[d]);
    char zn[n][3];
    char prz[] = ", ";
    for (int i = 1; i < n; ++i)
        strcpy(zn[i], prz);
    strcpy(zn[0], "");
    for (int i = 0; i < n; ++i){
        printf("%s", zn[i]);
        printf("%d", a[i]);
    }
    printf("\n");
}
 
void solve7(){
    struct pair a[n];
    int mx[8] = {}, my[8] = {};
    mx[4] = my[6] = 1;
    mx[5] = my[7] = -1;
    my[4] = mx[6] = 1;
    my[5] = mx[7] = -1;
    int (*func[10])(const void *, const void *);
    func[4] = func[5] = lesPair;
    func[6] = func[7] = lesPairObr;
 
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        a[i].x = x * mx[d];
        a[i].y = y * my[d];
    }
    qsort(a, n, sizeof(a[0]), func[d]);
    char zn[n][3];
    char prz[] = ", ";
    for (int i = 1; i < n; ++i)
        strcpy(zn[i], prz);
    strcpy(zn[0], "");
    for (int i = 0; i < n; ++i){
        printf("%s", zn[i]);                a[i].x /= mx[d];
        a[i].y /= my[d];
        printf("%d %d", a[i].x, a[i].y);
    }
 
    printf("\n");
}
 
void solveelse(){
    struct person a[n];
    for (int i = 0; i < n; ++i){
        char s[17];
        int val;
        scanf("%s %d", &s, &val);
        strcpy(a[i].name, s);
        a[i].salary = val;
    }
    int (*func[10])(const void *, const void *);
    func[8] = t8;
    func[9] = t9;
    qsort(a, n, sizeof(a[0]), func[d]);
    char zn[n][3];
    char prz[] = ", ";
    for (int i = 1; i < n; ++i)
        strcpy(zn[i], prz);
    strcpy(zn[0], "");
    for (int i = 0; i < n; ++i){
        printf("%s", zn[i]);
        printf("%s %d", a[i].name, a[i].salary);
    }
    printf("\n");
}
 
int main(int argc, char *argv[]) {
    //FILE *inp;
    //FILE *out;
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Clion\\input.txt", "r",  stdin);
    freopen("C:\\1\\work\\Clion\\output.txt", "w", stdout);
#endif
 
    int z;
    scanf("%d ", &z);
    while(z--){
 
        scanf("%d %d ", &n, &d);
        //exit(0);
        void (*solv[10])();
        for (int i = 0; i <= 3; ++i) solv[i] = solve3;
        for (int i = 4; i <= 7; ++i) solv[i] = solve7;
        for (int i = 8; i <= 9; ++i) solv[i] = solveelse;
        solv[d]();
    }
 
}