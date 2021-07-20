#include <iostream>
#include <time.h>
#include <complex>
#include <vector>
#include <stack>
 
#define y1 Y1
//#define pb push_back
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
class stackLong{
private:
    long long *a;
    int size, capac, maxSize;
public:
    stackLong(){a = new long long[15]; capac = 15; size = 0; maxSize = 15;}
    stackLong(int _capac){
        capac = _capac;
        size = 0;
        maxSize = capac;
        while(maxSize < size) maxSize <<= 1;
        a = new long long[maxSize];
    }
    ~stackLong(){delete[] a;}
    bool full(){ return size == capac;}
    bool empty(){return size == 0;}
    long long top(){
        if (!size) return 0;
        return a[size - 1];
    } // подумать о &
    void push(long long x){
        if (size == capac) return;
        a[size++] = x;
    }
    long long pop(){
        if (!size) return 0;
        return a[--size];
    }
    void clear(){size = 0;}
    void resize(int n){
        if (n <= capac) return;
        capac = n;
        if (n <= maxSize) return;
        if (!maxSize) maxSize = 1;
        while(maxSize < n) maxSize <<= 1;
        long long *b = new long long[maxSize];
        std::copy(a, a + size, b);
        delete[] a;
        a = b;
    }
};
 
class stackChar{
private:
    char *a;
    int _size, capac, maxSize;
public:
    stackChar(){a = new char[15]; capac = 15; _size = 0; maxSize = 15;}
    stackChar(int _capac){
        capac = _capac;
        _size = 0;
        maxSize = capac;
        while(maxSize < _size) maxSize <<= 1;
        a = new char[maxSize];
    }
    ~stackChar(){delete[] a;}
    bool full(){ return _size == capac;}
    bool empty(){return _size == 0;}
    int size(){ return _size;}
    char top(){
        if (!_size) return 0;
        return a[_size - 1];
    } // подумать о &
    void push(char x){
        if (_size == capac) return;
        a[_size++] = x;
    }
    char pop(){
        if (!_size) return 0;
        return a[--_size];
    }
    void clear(){_size = 0;}
    void resize(int n){
        if (n <= capac) return;
        capac = n;
        if (n <= maxSize) return;
        if (!maxSize) maxSize = 1;
        while(maxSize < n) maxSize <<= 1;
        char *b = new char[maxSize];
        std::copy(a, a + _size, b);
        delete[] a;
        a = b;
    }
};
 
 
int priority(const char _operator){
    int priorit = -1;
    switch (_operator){
        case '+':
        case '-': priorit = 1; break;
        case '*':
        case '/': priorit = 2; break;
        case '^': priorit = 3; break;
        case '(':
        case ')': priorit = -3; break;
    }
    return priorit;
}
 
long long pow(long long fir, long long sec){
    if (sec < 0) return 1;
    if (sec == 0) return 1;
    if (fir == 0) return 0;
    if (abs(fir) == 1) return fir;
    long long ans = 1;
    for (int i = 0; i < sec; ++i)
        ans *= fir;
    return ans;
}
 
 
long long runOperator(char oper, long long fir, long long sec){
    switch (oper){
        case '-': return fir - sec; break;
        case '+': return fir + sec; break;
        case '*': return fir * sec; break;
        case '/': return (sec ? fir / sec : 0); break;
        case '^': return pow(fir, sec); break;
    }
    cerr << "Uknown operator" << endl;
    exit(3);
}
 
 
long long solve(string s, const vector<long long> &val){
    int n = s.size();
    stackChar oper(n + 1);
    stackLong numb(n + 1);
    for (int i = 0; i < n; ++i){
        if (s[i] >= 'a' && s[i] <= 'z'){
            cout << s[i];
            numb.push(val[s[i] - 'a']);
        } else
        if (s[i] == '('){
            oper.push(s[i]);
        } else
        if (s[i] == ')'){
            while(true){
                char retOper = oper.pop();
                if (retOper == '(') break;
                cout << retOper;
                long long res = runOperator(retOper, numb.pop(), numb.pop());
                numb.push(res);
            }
        } else {
            while(!oper.empty() && priority(oper.top()) >= priority(s[i])){
                char retOper = oper.pop();
                cout << retOper;
                long long res = runOperator(retOper, numb.pop(), numb.pop());
                numb.push(res);
            }
            oper.push(s[i]);
        }
    }
    cout << '\n';
    //    if (!oper.empty()){
    //        cerr << "Additional operator at the end of processing" << endl;
    //        exit(4);
    //    }
    return numb.top();
}
int main(int argc, char* argv[]){
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
#endif
    int z;
    cin >> z;
    while(z--) {
        vector < long long > zn(27, 0);
        for (int i = 0; i < 26; ++i)
            cin >> zn[i];
        int q;
        cin >> q;
        string s;
        for (int i = 0; i < q; ++i){
            cin >> s;
            s = "(" + s + ")";
            cout << solve(s, zn) << '\n';
        }
 
    }
}