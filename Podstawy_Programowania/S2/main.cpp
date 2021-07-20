#include <bits/stdc++.h>
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
 
bool check(string f, string s){
    if (abs((int)(f.size()) -  (int)(s.size())) > 1) return false;
    int i = 0, j = 0;
    bool byl = false;
    while(i < f.size() || j < s.size()){
        if (i >= f.size() || j >= s.size()){
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
        if (f.size() < s.size()) ++j; else
        if (s.size() < f.size()) ++i; else{
            ++i;
            ++j;
        }
    }
    return true;
}
 
int main(int argc, char* argv[]){
    ifstream cin;
    ofstream cout;
    string slowo;
    #ifdef Estb_probitie
        //freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
        //freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
        cin.open("C:\\1\\work\\Satori_pp\\input.txt");
        cout.open("C:\\1\\work\\Satori_pp\\output.txt");
        cin >> slowo;
        cin.get();
    #else
        if (argc < 4) exit(0);
        cin.open(argv[1]);
        if (!cin.is_open()) exit(0);
        cout.open(argv[2]);
        slowo = argv[3];
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for (int i = 0; i < slowo.size(); ++i)
 
        slowo[i] = tolower(slowo[i]);
    int zvez = -2, slas = -2;
    int lineCnt = 1;
    vector < pair < int , string > > ans;
    string word;
    int commLvl = 0, now = 0, allWords = 0;
    char c;
    char buff[7];
    int i = 5, rd = 0;
 
    while(true) {
        bool byl = false;
        while (i != rd && cin.get(buff[rd])){
            ++rd;
            if (rd == 6) rd = 0;
            byl = true;
        }
        ++i;
        i %= 6;
        char c = buff[i];
        char nx = buff[(i + 1) % 6];
        c = tolower(c);
        //cout << word _ commLvl << '\n';
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
                if (!word.empty()) word += c;
            } else
            if (c >= 'a' && c <= 'z'){
                word += c;
            }  else {
                if (!word.empty())
                    ++allWords;
                if (check(word, slowo)){
                    ans.pb({lineCnt, word});
                }
                word = {};
                if (c == '\n'){
                    ++lineCnt;
                }
            }
        }
        i %= 6;
        buff[i] = '-';
        if (!byl && i == rd) break;
    }
    for (auto i : ans){
        cout << "Linia " << i.first << ": " << i.second << '\n';
    }
    cout << "Wyrazy: " << allWords << '\n';
    cout << "Wyrazy specjalne: " << ans.size() << '\n';
    cout.close();
    cin.close();
}