#ifndef SATORI_MP_SOLUTION_H
#define SATORI_MP_SOLUTION_H
#include <vector>
#include <algorithm>
 
template <class T>
class myPair {
public:
  T first, second;
};
 
template <class T, class cmp>
class stackMin {
  vector < pair <T, T> > stack;
  cmp cmpType;
public:
  explicit stackMin(int size = 4) {
    stack.reserve(size);
  }
  void push(T element) {
    stack.push_back({element, element});
    if (stack.size() > 1 && !cmpType(element, stack[stack.size() - 2].second))
      stack.back().second = stack[stack.size() - 2].second;
  }
  bool pop() {
    if (stack.empty()) return false;
    stack.pop_back();
    return true;
  }
  T top() { return stack.back().first; }
  T min() { return stack.back().second; }
  void clear() { stack.clear(); }
  bool empty() { return stack.empty(); }
};
 
template <class T, class cmp>
class queueMin {
  vector< pair <T, T> > toPop, toAdd;
  cmp cmpType;
public:
  explicit queueMin(int size = 4) {
    toPop.reserve(4);
    toAdd.reserve(4);
  }
  void enqueue(T element) {
    toAdd.push_back({element, element});
    if (toAdd.size() > 1 && !cmpType(element, toAdd[toAdd.size() - 2].second))
      toAdd.back().second = toAdd[toAdd.size() - 2].second;
  }
  bool dequeue() {
    if (toPop.empty() && toAdd.empty()) return false;
    if (!toPop.empty()) {
      toPop.pop_back();
      return true;
    }
    reverse(toAdd.begin(), toAdd.end());
    toPop = toAdd;
    toAdd.clear();
    for (int i = 0; i < toPop.size(); ++i) {
      toPop[i].second = toPop[i].first;
      if (i && !cmpType(toPop[i].second, toPop[i - 1].second))
        toPop[i].second = toPop[i - 1].second;
    }
    toPop.pop_back();
    return true;
  }
  T front() { return (toPop.empty() ? toAdd[0].first : toPop.back().first); }
  T min() {
    if (toAdd.empty()) return toPop.back().second;
    if (toPop.empty()) return toAdd.back().second;
    if (cmpType(toAdd.back().second, toPop.back().second)) return toAdd.back().second;
    return toPop.back().second;
  }
  bool empty() { return (toPop.empty() && toAdd.empty()); }
  void clear() {
    toAdd.clear();
    toPop.clear();
  }
};
 
template <typename T, typename O>
void solveStack(stackMin<T, O> &stack, int n) {
  for (int i = 0; i < n; ++i) {
    string command;
    cin >> command;
    if (command == "push") {
      T x;
      cin >> x;
      stack.push(x);
      continue;
    } else if (command == "pop") {
      if (stack.empty()) cout << "ERROR"; else {
        cout << stack.top();
        stack.pop();
      }
    } else if (command == "top") {
      if (stack.empty()) cout << "EMPTY"; else cout << stack.top();
    } else if (command == "min") {
      if (stack.empty()) cout << "EMPTY"; else cout << stack.min();
    } else if (command == "clear") {
      stack.clear();
      continue;
    } else if (command == "empty") {
      cout << (stack.empty() ? "YES" : "NO");
    }
    cout << '\n';
  }
}
template <typename T, typename O>
void solveQueue(queueMin<T, O> &queue, int n) {
  for (int i = 0; i < n; ++i) {
    string command;
    cin >> command;
    if (command == "enqueue") {
      T x;
      cin >> x;
      queue.enqueue(x);
      continue;
    } else if (command == "dequeue") {
      if (queue.empty()) cout << "ERROR"; else {
        cout << queue.front();
        queue.dequeue();
      }
    } else if (command == "front") {
      if (queue.empty()) cout << "EMPTY"; else cout << queue.front();
    } else if (command == "min") {
      if (queue.empty()) cout << "EMPTY"; else cout << queue.min();
    } else if (command == "clear") {
      queue.clear();
      continue;
    } else if (command == "empty") {
      cout << (queue.empty() ? "YES" : "NO");
    }
    cout << '\n';
  }
}
 
#endif //SATORI_MP_SOLUTION_H
