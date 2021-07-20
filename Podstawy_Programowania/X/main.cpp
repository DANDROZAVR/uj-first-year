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
 
class person {
    string name;
    short int age;
    int item;
    person *next;
public:
    //~person(){delete next;}
    person(){next = nullptr;}
    person(string _name, short int _age, int _item){name = _name; age = _age; item = _item;}
    //person getPerson(){return person(name, age, item);}
    person* getNext(){return next;}
    short int getAge(){return age;}
    int getItem(){return item;}
    string getName(){return name;}
    friend class list;
};
 
class list {
    person *head;
    int size;
    short int maxAge;
public:
    list(){head = new person; size = 0;}
    ~list(){
        person *now = head;
        person *last = head;
        for (int i = 0; i <= size; ++i){
            last = now;
            now = now->getNext();
            delete last;
        }
    }
    list(short int _age){maxAge = _age; size = 0; head = new person;}
    person* getHead(){return head;}
    bool insert(int pos, string _name, short int _age, int _item) {
        if (pos < 1 || pos > size + 1) return false;
        pos = size - pos + 1;
        person *last = head;
        for (int i = 0; i < pos; ++i) {
            last = last->getNext();
        }
        //cout << last->getName() _ pos _ _name << endl;
        if (last == nullptr) exit(1);
        person *afterLast = last->getNext();
        person *p = new person(_name, _age, _item);
        last->next = p;
        p->next = afterLast;
        ++size;
        return true;
    }
 
    bool addNew(string _name, short int _age, int _item) {
        if (_age >= maxAge) {
            return insert(1, _name, _age, _item);
        } else {
            return insert(size + 1, _name, _age, _item);
        }
    }
    bool popFront() {
        if (!size) return false;
        person *now = head;
        for (int i = 0; i + 1 < size; ++i) {
            now = now->getNext();
        }
        delete now->getNext();
        --size;
        return true;
    }
    bool popBack() {
        if (!size) return false;
        person *first = head->getNext();
        person *second = first->getNext();
        head->next = second;
        --size;
        return true;
    }
    bool eraseByName(string _name, short int _age) {
        person *now = head, *last = nullptr;
        bool byl = false;
        int all = 0;
        for (int i = 0; i < size; ++i){
            last = now;
            now = now->getNext();
            if (now->getAge() == _age && now->getName() == _name) {
                byl = true;
                last->next = now->getNext();
                delete now;
                now = last;
                ++all;
            }
        }
        size -= all;
        return byl;
    }
    bool print(){
        if (!size) return false;
        person *now = head;
        vector < pair < pair < string , int > , int > > ans;
        for (int i = 0; i < size; ++i){
            now = now->getNext();
            ans.pb({{now->getName(), now->getAge()}, now->getItem()});
        }
        for (int i = (int)(ans.size()) - 1; i >= 0; --i)
            cout << ans[i].first.first _ ans[i].first.second _ ans[i].second << '\n';
        return true;
    }
    void clean(){
        person *now = head;
        person *last = head;
        for (int i = 0; i < size; ++i){
            last = now;
            now = now->getNext();
            if (i) delete last;
        }
        size = 0;
    }
    void eraseByProduct(int _item){
        if (!size) return;
        int all = 0;
        person *now = head, *last;
        for (int i = 0; i < size; ++i) {
            last = now;
            now = now->getNext();
            if (now->getItem() == _item) {
                last->next = now->getNext();
                delete now;
                now = last;
                ++all;
            }
        }
        size -= all;
    }
    bool reverse(){
        if (!size) return false;
        person* now = head, *last;
        int oldSize = size;
        for (int i = 0; i < oldSize; ++i) {
            //print(); cout << endl;
            last = now;
            now = now->getNext();
            if (i) delete last;
            insert(size + 1, now->getName(), now->getAge(), now->getItem());
            --size;
        }
        size = oldSize;
        return true;
    }
    void changeAge(short int _age){
        if (_age > maxAge){
            maxAge = _age;
            return;
        }
        person *now = head;
        person *last;
        maxAge = _age;
        person *listEnd = head;
        for (int i = 0; i < size; ++i) listEnd = listEnd->getNext();
        for (int i = 0; i < size; ++i){
            last = now;
            now = now->getNext();
            if (now->getAge() >= _age){
                //cout << i _ now->getName() _ listEnd-><< '\n';
                listEnd->next = now;
                last->next = now->getNext();
                listEnd = now;
                now = last;
            }
        }
    }
};
 
int main(int argc, char* argv[]){
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
#endif
    int q;
    cin >> q;
    while(q--){
        int n, w;
        cin >> n >> w;
        list que(w);
        for (int i = 0; i < n; ++i){
            //cerr << i << endl;
            string s;
            cin >> s;
            bool bad = false;
            if (s == "INSERT") {
                string name; short int age; int pos, item;
                cin >> name >> age >> pos >> item;
                if (!que.insert(pos, name, age, item)) bad = true;
            } else
            if (s == "NEW"){
                string name; short int age; int item;
                cin >> name >> age >> item;
                que.addNew(name, age, item);
            } else
            if (s == "BUYING"){
                if (!que.popFront()) bad = true;
            } else
            if (s == "RESIGNATION"){
                if (!que.popBack()) bad = true;
            } else
            if (s == "DELETE"){
                string name; short int age;
                cin >> name >> age;
                if (!que.eraseByName(name, age)) bad = true;
            } else
            if (s == "PRINT"){
                if (!que.print()) cout << "EMPTY\n";
            } else
            if (s == "REVERSE"){
                if (!que.reverse()) cout << "EMPTY\n";
            } else
            if (s == "CHANGE"){
                short int age;
                cin >> age;
                que.changeAge(age);
            } else
            if (s == "LACK"){
                int item;
                cin >> item;
                que.eraseByProduct(item);
            } else
            if (s == "CLEAN"){
                que.clean();
            }
            if (bad) cout << "ERROR\n";
        }
    }
}