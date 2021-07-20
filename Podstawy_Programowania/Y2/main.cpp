#include <iostream>
#include <complex>
#include <vector>
 
 
#define y1 Y1
//#define pb push_back
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
 
 
class person {
    string name;
    int score;
    person *next, *prev;
public:
    //~person(){delete next;}
    person(){next = prev = nullptr; score = 0;}
    person(string _name, int _score){name = _name; score = _score; next = prev = nullptr;}
    person(string _name, int _score, person *_prev, person *_next){name = _name; score = _score; prev = _prev; next = _next;}
    person *getNext(){return next;}
    person *getPrev(){return prev;}
    string getName(){return name;}
    int getScore(){return score;}
    friend class list;
};
 
class list {
    person *head, *tail;
    int size;
public:
    void initForScore(){tail->score = 2e9; head->score = -2e9;}
    list(){head = new person("0", 0); tail = new person("{", 0); head->next = tail; tail->prev = head;size = 0;}
    ~list(){
        clean();
        delete head;
        delete tail;
    }
    bool insert(int pos, person *p) {
        person *last = head;
        for (int i = 0; i < pos; ++i) {
            last = last->getNext();
        }
        if (last == nullptr) exit(1);
        person *afterLast = last->getNext();
        last->next = p;
        p->next = afterLast; p->prev = last;
        afterLast->prev = p;
        ++size;
        return true;
    }
    bool popFront() {
        if (!size) return false;
        person *now = head;
        for (int i = 0; i < size; ++i) {
            now = now->getNext();
        }
        delete now->getNext();
        tail->prev = now;
        --size;
        return true;
    }
    bool popBack() {
        if (!size) return false;
        person *first = head->getNext();
        person *second = first->getNext();
        head->next = second;
        second->prev = head;
        --size;
        return true;
    }
    bool eraseByPosition(int pos) {
        person *last = head;
        for (int i = 0; i < pos; ++i){
            last = last->next;
        }
        auto now = last->next;
        last->next = now->next;
        (now->next)->prev = last;
        delete now;
        --size;
        return true;
    }
    bool print(){
        if (!size) return false;
        person *now = head;
        for (int i = 0; i < size; ++i) {
            now = now->next;
            cout << now->name << " " << now->score << '\n';
        }
        return true;
    }
    bool rprint(){
        if (!size) return false;
        person *now = tail;
        for (int i = 0; i < size; ++i) {
            now = now->prev;
            cout << now->name << " " << now->score << '\n';
        }
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
        tail->prev = head;
        head->next = tail;
        size = 0;
    }
    pair < int, person*> findByName(string name, bool shouldBe){
        int it = -1;
        person *now = head;
        while(name > now->name){
            now = now->next;
            ++it;
        }
        return {it, now};
    }
    int findByScore(int score, string name, bool shouldBe){
        int it = -1;
        person *now = head;
        while(score > now->score || (score == now->score && name > now->name)){
            now = now->next;
            ++it;
        }
        //cout << name _ it _ now->name _ size << '\n';
        return it;
    }
    void addScore(int pos, int score){
        person *now = head;
        for (int i = 0; i <= pos; ++i) now = now->next;
        now->score = max(0, now->score + score);
    }
};
 
class solver{
    list listByName, listByScore;
public:
    solver(){listByScore.initForScore();}
    void add(string name, int score){
//        if (name == "U" && score == 84){
//            cout << "tuk";
//        }
        auto elem = listByName.findByName(name, false);
        int rscore = elem.second->getScore();
        if (elem.second->getName() != name){
            int pos1 = elem.first;
            int pos2 = listByScore.findByScore(score, name, false);
            listByName.insert(pos1, new person(name, score));
            listByScore.insert(pos2, new person(name, score));
        } else {
            int pos1 = elem.first;
            int pos2 = listByScore.findByScore(rscore, name, true);
            listByName.addScore(pos1, score);
            listByScore.eraseByPosition(pos2);
            int npos2 = listByScore.findByScore(rscore + score, name, false);
            listByScore.insert(npos2, new person(name, score + rscore));
        }
    }
    static void error(string name){
        cout << "ERROR " << name << '\n';
    }
    void erase(string &name) {
        auto elem = listByName.findByName(name, true);
        if (elem.second->getName() != name) {
            error(name);
            return;
        }
        int pos2 = listByScore.findByScore(elem.second->getScore(), name, 0);
        listByName.eraseByPosition(elem.first);
        listByScore.eraseByPosition(pos2);
    }
    void find(string name) {
        auto elem = listByName.findByName(name, true);
        if (elem.second->getName() == name) {
            cout << name << " " << elem.second->getScore() << '\n';
            return;
        }
        error(name);
    }
    void correct(string name, int addScore){
        auto elem = listByName.findByName(name, 1);
        if (elem.second->getName() != name){
            error(name);
            return;
        }
        int score = elem.second->getScore();
        person *newPerson = new person(name, max(score + addScore, 0));
        int pos2 = listByScore.findByScore(score, name, 1);
 
        listByName.addScore(elem.first, addScore);
        listByScore.eraseByPosition(pos2);
        int npos2 = listByScore.findByScore(max(score + addScore, 0), name, 1);
        listByScore.insert(npos2, newPerson);
    }
    void changeName(string name, string name2){
        auto elem = listByName.findByName(name, true);
        int rscore = elem.second->getScore();
        int score = elem.second->getScore();
        if (elem.second->getName() != name || listByName.findByName(name2, false).second->getName() == name2){
            error(name + " " + name2);
            return;
        }
        listByName.eraseByPosition(elem.first);
        int npos1 = listByName.findByName(name2, false).first;
        listByName.insert(npos1, new person(name2, score));
 
        int pos2 = listByScore.findByScore(rscore, name, true);
        listByScore.eraseByPosition(pos2);
        int npos2 = listByScore.findByScore(rscore, name2, false);
        listByScore.insert(npos2, new person(name2, score));
    }
    void printName(bool desc = false){
        bool empty = false;
        if (desc == false)
            empty = !listByName.print(); else
            empty = !listByName.rprint();
        if (empty == true) cout << "EMPTY\n";
    }
    void printScore(bool desc = false){
        bool empty = false;
        if (desc == false)
            empty = !listByScore.print(); else
            empty = !listByScore.rprint();
        if (empty == true) cout << "EMPTY\n";
    }
    void clean(){
        listByName.clean();
        listByScore.clean();
        cout << "CLEAN OK\n";
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
        int n;
        cin >> n;
        solver solve;
        for (int i = 0; i < n; ++i){
            string oper;
            cin >> oper;
            if (oper == "ADD"){
                string name; int score;
                cin >> name >> score;
                solve.add(name, score);
            } else
            if (oper == "DISQ"){
                string name;
                cin >> name;
                solve.erase(name);
            } else
            if (oper == "FIND"){
                string name;
                cin >> name;
                solve.find(name);
            } else
            if (oper == "CORRECT"){
                string name; int score;
                cin >> name >> score;
                solve.correct(name, score);
            } else
            if (oper == "CHANGE"){
                string name, name2;
                cin >> name >> name2;
                solve.changeName(name, name2);
            } else
            if (oper == "PRINT"){
                solve.printName();
            } else
            if (oper == "PRINT_DESC"){
                solve.printName(true);
            } else
            if (oper == "RANKING"){
                solve.printScore();
            } else
            if (oper == "RANKING_DESC"){
                solve.printScore(true);
            } else
            if (oper == "CLEAN"){
                solve.clean();
            } else exit(2);
//            cout<<endl;
        }
 
    }
}