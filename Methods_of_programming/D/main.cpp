#include <bits/stdc++.h>
template <class T>
class node {
public:
  T name;
  node **near;
  node() {
    near = new node <T>* [2];
    near[0] = nullptr;
    near[1] = nullptr;
  }
  node(T _name, node* brother, node* sister) {
    name = _name;
    near = new node <T> *[2];
    near[0] = brother; near[1] = sister;
  }
  ~node() {
    delete[] near;
  }
};
 
template <class T>
class doubleList {
  node<T> *head, *tail;
  void changeNeighbour(node <T> *now, node <T> *lastNeighbour, node <T> *newNeighbour) {
    now->near[now->near[0] != lastNeighbour] = newNeighbour;
  }
  node <T> * neighbourExceptOf(node <T> *now, node <T> *other) {
    return now->near[now->near[0] == other];
  }
public:
  explicit doubleList() {
    head = new node <T>();
    tail = new node <T>();
    head->near[1] =  tail; // the second value is always not nullptr
    tail->near[1] =  head;
  }
  ~doubleList() {
    clean();
    delete head;
    delete tail;
  }
  void addFirst(T& name) {
    node <T> * newFirst = new node <T> (name, head, head->near[1]);
    changeNeighbour(head->near[1], head, newFirst);
    changeNeighbour(head, head->near[1], newFirst);
  }
  void addFirst(node <T> *newFirst) {
    newFirst->near[0] = head;
    newFirst->near[1] = head->near[1];
    changeNeighbour(head->near[1], head, newFirst);
    changeNeighbour(head, head->near[1], newFirst);
  }
  void addLast(T& name) {
    node <T> * newLast = new node <T> (name, tail, tail->near[1]);
    changeNeighbour(tail->near[1], tail, newLast);
    changeNeighbour(tail, tail->near[1], newLast);
  }
  void addLast(node <T> *newLast) {
    newLast->near[0] = tail;
    newLast->near[1] = tail->near[1];
    changeNeighbour(tail->near[1], tail, newLast);
    changeNeighbour(tail, tail->near[1], newLast);
  }
  node <T>* detachFront() {
    auto delNode = head->near[1];
    if (delNode == tail) return nullptr;
    auto newFirst = neighbourExceptOf(delNode, head);
    changeNeighbour(head, delNode, newFirst);
    changeNeighbour(newFirst, delNode, head);
    return delNode;
  }
  node<T>* detachLast() {
    auto delNode = tail->near[1];
    if (delNode == head) return nullptr;
    auto newLast = neighbourExceptOf(delNode, tail);
    changeNeighbour(tail, delNode, newLast);
    changeNeighbour(newLast, delNode, tail);
    return delNode;
  }
  void reverse() {
    std::swap(head, tail);
  }
  void unionn(doubleList <T> &list) {
    changeNeighbour(tail->near[1], tail, list.head->near[1]);
    changeNeighbour(list.head->near[1], list.head, tail->near[1]);
    changeNeighbour(list.tail->near[1], list.tail, tail);
    changeNeighbour(tail, tail->near[1], list.tail->near[1]);
    list.oldTrain();
  }
  void clean() {
    auto actual = head->near[1];
    auto prev = head;
    while(actual != tail) {
      auto next = neighbourExceptOf(actual, prev);
      prev = actual;
      delete actual;
      actual = next;
    }
    head->near[1] = tail;
    tail->near[1] = head;
  }
  void print(T& objectName) {
    auto actual = head->near[1];
    auto prev = head;
    std::cout << char(34) << objectName << char(34) << ":" << '\n';
    while(actual != tail) {
      if (prev != head) std::cout << "<-";
      std::cout << actual->name;
      auto temp = actual;
      actual = neighbourExceptOf(actual, prev);
      prev = temp;
    }
    std::cout << '\n';
  }
  void oldTrain() {
    head->near[1] = tail;
    tail->near[1] = head;
  }
};
 
struct Solver {
  void Solve() {
    int n;
    std::cin >> n;
    std::map<std::string, doubleList<std::string> *> mp;
    while (n--) {
      std::string command;
      std::string train, child, train2;
      std::cin >> command;
      if (command == "NEW") {
        std::cin >> train >> child;
        auto newList = new doubleList<std::string>;
        newList->addFirst(child);
        mp[train] = newList;
      } else if (command == "BACK") {
        std::cin >> train >> child;
        mp[train]->addLast(child);
      } else if (command == "FRONT") {
        std::cin >> train >> child;
        mp[train]->addFirst(child);
      } else if (command == "PRINT") {
        std::cin >> train;
        mp[train]->print(train);
      } else if (command == "REVERSE") {
        std::cin >> train;
        mp[train]->reverse();
      } else if (command == "DELFRONT") {
        std::cin >> train >> train2;
        auto newChild = mp[train2]->detachFront();
        auto newTrain = new doubleList<std::string>;
        newTrain->addFirst(newChild);
        mp[train] = newTrain;
      } else if (command == "DELBACK") {
        std::cin >> train2 >> train;
        auto newChild = mp[train2]->detachLast();
        auto newTrain = new doubleList<std::string>;
        newTrain->addFirst(newChild);
        mp[train] = newTrain;
      } else if (command == "UNION") {
        std::cin >> train >> train2;
        auto *mppTrain = mp[train2];
        mp[train]->unionn(*mppTrain);
        mp.erase(train2);
        delete mppTrain;
      }
    }
    for (auto i : mp)
      delete i.second;
  }
};
 
int main() {
#ifdef Estb_probitie
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int T;
  std::cin >> T;
  while(T--) {
    Solver solution;
    solution.Solve();
  }
  return 0;
}
