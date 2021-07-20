#include <bits/stdc++.h>
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
 
bool solve(string text, string word, int skip, int &N){
    text = " " + text;
    int n = word.size();
    int m = text.size();
    bool dp[m][n + 1];
    //cout << text _ word << '\n';
    for (int i = 0; i < m; ++i) {
        memset(dp[i], 0, sizeof(dp[i]));
        dp[i][0] = true;
    }
    for (int i = 0; i < n; ++i)
        if (word[i] != '*') break; else dp[0][i + 1] = true;
    for (int i = 1; i < m; ++i){
        for (int j = 1; j <= n; ++j){
            if (dp[i - 1][j - 1]) {
                if (word[j - 1] == text[i] || word[j - 1] == '?' || word[j - 1] == '*') dp[i][j] = true;
            }
            if (dp[i - 1][j] && word[j - 1] == '*')
                dp[i][j] = true;
            if (dp[i][j - 1] && word[j - 1] == '*')
                dp[i][j] = true;
            //cout << dp[i][j] _ word[j - 1] << '\n';
        }
    }
    for (int i = m - 1; i >= 0; --i)
        if (dp[i][n]){
            N = m - i - 1 + skip;
            return true;
        }
    return false;
}
 
void search(string text, string word, int &N){
    reverse(text.begin(), text.end());
    reverse(word.begin(), word.end());
    int n = word.size();
    int m = text.size(), skip = 0;
    string now;
    for (int i = m - 1; i >= 0; --i){
        if (text[i] == ' ' || i == 0){
            if (!i && text[i] != ' ') now += text[i];
            reverse(now.begin(), now.end());
            if (solve(now, word, skip, N)) return;
            skip += now.size() + 1;
            now = {};
            continue;
        }
        now += text[i];
    }
    N = -1;
}
 
int main(int argc, char* argv[]){
    #ifdef Estb_probitie
        freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
        freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int z;
    cin >> z;
    string empt;
    getline(cin, empt);
    while(z--){
        string text;
        getline(cin, text);
        string pattern;
        getline(cin, pattern);
        int ans;
        search(text, pattern, ans);
        //cout << ans << '\n';
        if (ans == -1) cout << "NIE\n"; else cout << "TAK " << ans << '\n';
    }
}