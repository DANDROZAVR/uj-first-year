#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
 
 
bool check(char f[], char s[]){
    int n = 0, m = 0;
    while(f[n]) ++n;
    while(s[m]) ++m;
    if (abs(n - m) > 1) return false;
    int i = 0, j = 0;
    bool byl = false;
    while(i < n || j < m){
        if (i >= n || j >= m){
            if (byl) return false;
            byl = true;
            ++i;
            ++j;
            continue;
        }
        if (f[i] == s[j]){
            ++i;
            ++j;
            continue;
        }
        if (byl) return false;
        byl = true;
        if (n < m) ++j; else
        if (m < n) ++i; else{
            ++i;
            ++j;
        }
    }
    return true;
}
 
int main(int argc, char* argv[]){
    FILE *cin, *cout;
    char slowo[32];
#ifdef Estb_probitie
    //freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
    //freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
    cin = fopen("C:\\1\\work\\Clion\\input.txt", "r");
    cout = fopen("C:\\1\\work\\Clion\\output.txt", "w");
    fscanf(cin, "%s\n", &slowo);
#else
    if (argc < 4) exit(0);
        cin = fopen(argv[1], "r");
        if (!cin) exit(0);
        cout = fopen(argv[2], "w");
        strcpy(slowo, argv[3]);
#endif
    for (int i = 0; slowo[i]; ++i)
        slowo[i] = tolower(slowo[i]);
    int zvez = -2, slas = -2;
    int lineCnt = 1, wordSz = 0;
    char word[34];
    memset(word, 0, 34);
    int commLvl = 0, now = 0, allWords = 0, ans = 0, i = 5, rd = 0;;
    char c, buff[7];
    const int N = 10000;
    char ansWord[N][32];
    int ansLine[N];
 
    while(true) {
        bool byl = false;
        while (i != rd && fscanf(cin, "%c", &buff[rd]) == 1){
            ++rd;
            if (rd == 6) rd = 0;
            byl = true;
        }
        ++i;
        i %= 6;
        char c = buff[i];
        char nx = buff[(i + 1) % 6];
        c = tolower(c);
        //   printf("%s %s\n", word, slowo);
        if (c == '/' && nx == '*'){
            buff[i] = '-';
            ++commLvl;
            ++i;
        } else
        if (c == '*' && nx == '/' && commLvl){
            buff[i] = '-';
            --commLvl;
            ++i;
        } else
        if (!commLvl){
            if (c >= '0' && c <= '9'){
                if (wordSz && wordSz <= 32) word[wordSz++] = c;
            } else
            if (c >= 'a' && c <= 'z'){
                if (wordSz <= 32) word[wordSz++] = c;
            }  else {
                if (wordSz)
                    ++allWords;
                if (check(word, slowo)){
                    ansLine[ans] = lineCnt;
                    strcpy(ansWord[ans++], word);
                }
                memset(word, 0, wordSz);
                wordSz = 0;
                if (c == '\n'){
                    ++lineCnt;
                }
            }
        }
        i %= 6;
        buff[i] = '-';
        if (!byl && i == rd) break;
    }
    for (int i = 0; i < ans; ++i)
        fprintf(cout, "Linia %d: %s\n", ansLine[i], ansWord[i]);
    fprintf(cout, "Wyrazy: %d\n", allWords);
    fprintf(cout, "Wyrazy specjalne: %d\n", ans);
    fclose(cin);
    fclose(cout);
}