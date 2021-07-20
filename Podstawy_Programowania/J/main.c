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
char *shf[259];
 
void Init(){
    shf['a']="1110";       shf['b']="1000111";
    shf['c']="10111";      shf['d']="10000111";
    shf['e']="1001";       shf['f']="1000100";
    shf['g']="1000110";    shf['h']="1000101";
    shf['i']="1100";       shf['j']="111110";
    shf['k']="00011";      shf['l']="1000001";
    shf['m']="1000000";    shf['n']="0101";
    shf['o']="1010";       shf['p']="00010";
    shf['q']="100001001";  shf['r']="0100";
    shf['s']="11011";      shf['t']="11010";
    shf['u']="111111";     shf['v']="100001000";
    shf['w']="11110";      shf['x']="10000101";
    shf['y']="10110";      shf['z']="0010";
    shf[' ']="0111";       shf['.']="0110";
    shf['\n']="0011";
}
 
#define N 16000000
bool ans[N];
 
int main(int argc, char *argv[]){
    FILE *inp;
    FILE *out;
    Init();
    int a;
    #ifdef Estb_probitie
        inp = fopen("C:\\1\\work\\Clion\\input.txt", "r");
        out = fopen("C:\\1\\work\\Clion\\output.txt", "w+b");
        a = 2;
    #else
        a = argv[3][0] - '0';
        inp = fopen(argv[1], "rb");
        out = fopen(argv[2], "w");
    #endif
//    if (inp == NULL || out == NULL) exit(0);
    if (a == 1) {
        char let;
        int now = 0;
        while (fread(&let, sizeof(char), 1, inp)) {
            int n = 0;
            while (shf[let][n])
                ans[now++] = shf[let][n++] - '0';
        }
 
//        printf("%d", now);
        while (now % 8 != 0) ans[now++] = 0;
        for (int i = 0; i < now / 8; ++i){
            unsigned char let = 0;
            for (int j = i * 8; j < (i + 1) * 8; ++j) {
                let = let * 2 + ans[j];
            }
            fwrite(&let, sizeof(char), 1, out);
        }
 
    } else{
        unsigned char let;
        int now = 0;
        while (fread(&let, sizeof(char), 1, inp)) {
            char tek[15];
            int n = 0;
            while (let) {
                tek[n++] = let % 2;
                let /= 2;
            }
            while(n < 8)
                tek[n++] = 0;
            for (int i = 0; i < n; ++i)
                ans[now++] = tek[n - i - 1];
        }
        int rd = 0, nakop = 0;
        char otv[20];
        memset(otv, 0, 20);
        while(rd < now){
            otv[nakop++] = ans[rd++] + '0';
            for (char i = 'a'; i <= 'z'; ++i)
                if (strlen(shf[i]) == nakop && strcmp(shf[i], otv) == 0) {
                    fwrite(&i, sizeof(char), 1, out);
                    for (int i = 0; i < nakop; ++i)
                        otv[i] = 0;
                    nakop = 0;
                    break;
                }
 
            unsigned char car = '\n';
            if (strlen(shf[car]) == nakop && strcmp(shf[car], otv) == 0) {
                fwrite(&car, sizeof(char), 1, out);
                for (int i = 0; i < nakop; ++i)
                    otv[i] = 0;
                nakop = 0;
            } car = '.';
            if (strlen(shf[car]) == nakop && strcmp(shf[car], otv) == 0) {
                fwrite(&car, sizeof(char), 1, out);
                for (int i = 0; i < nakop; ++i)
                    otv[i] = 0;
                nakop = 0;
            } car = ' ';
            if (strlen(shf[car]) == nakop && strcmp(shf[car], otv) == 0) {
                fwrite(&car, sizeof(char), 1, out);
                for (int i = 0; i < nakop; ++i)
                    otv[i] = 0;
                nakop = 0;
            }
        }
//            exit(0);
    }
 
    fclose(inp);
    fclose(out);
}