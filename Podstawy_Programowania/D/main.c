#include <stdio.h>
#include <math.h>
 
 
int main() {
    int test;
    scanf("%d", &test);
    while(test--){
        double x, y, c;
        scanf("%lf %lf %lf", &x, &y, &c);
        double l = 0, r = x;
        if (r > y) r = y;
        while(r - l >= 0.000001){
            double mid = (l + r) / 2;
            double b1 = sqrt(x * x - mid * mid);
            double k1 = (-b1) / mid;
            double ff = sqrt(y * y - mid * mid);
            double b2 = 0, k2 = sqrt(y * y - mid * mid) / mid;
            double x = ((b2 - b1) / (k1 - k2));
            if (x < 0) x *= -1;
            double y = k1 * x + b1;
            if (y < c){
                r = mid;
            }   else{
                l = mid;
            }
            //printf("%f %f %f %f %f %f %f\n", k1, b1, k2, b2, x, y, mid);
           // return 0;
        }
        printf("%.3f\n", l);
        //return 0;
    }
}