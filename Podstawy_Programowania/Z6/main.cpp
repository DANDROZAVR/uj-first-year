#include <iostream>
#include <complex>
#include <vector>
 
 
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
const int N = 4e6;
int ans[N];
int main(int argc, char* argv[]){
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
#endif
    int z;
    std::cin >> z;
    while(z--){
        int n;
        std::cin >> n;
        n = n * 2;
        int a[n];
        bool byl[n];
        std::fill(byl, byl + n, 0);
        int prev[n + 1], number[n + 1];
        std::fill(number, number + n, -1);
        for (int i = 0; i < n; ++i)
            prev[i] = i - 1;
        int notClose[n + 1], all = 0, otv = 0;
        for (int i = 0; i < n; ++i){
            std::cin >> a[i];
            if (byl[a[i]]) {
                int pos = number[a[i]];
                if (pos == -1) exit(1);
                for (int j = pos; j + 1 < all; ++j){
                    ans[otv++] = j;
                    std::swap(number[notClose[j]], number[notClose[j + 1]]);
                    std::swap(notClose[j], notClose[j + 1]);
                }
                --all;
            } else {
                byl[a[i]] = true;
                notClose[all] = a[i];
                number[a[i]] = all;
                ++all;
            }
        }
        std::cout << otv << '\n';
        for (int i = 0; i < otv; ++i)
            std::cout << ans[i] + 1 << " ";
        std::cout << '\n';
    }
}