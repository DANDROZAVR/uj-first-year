#ifndef SATORI_MP_SOLUTION_H
#define SATORI_MP_SOLUTION_H
#include <vector>
#include <algorithm>
#include <iostream>
 
template <class K, class V>
struct node {
  K key;
  V value;
  node* left,* right,* anc;
  explicit node(K _key, V _value) {
    key = _key;
    value = _value;
    left = right = anc = nullptr;
  }
  K GetKey(){ return key; }
  V GetName(){ return value; }
 
  void changeName(V name){ value = name; }
};
template <class K, class V>
std::ostream& operator<<(std::ostream& st, node<K, V>& a) {
  st << a.GetKey() << " " << a.GetName() << '\n';
  return st;
}
 
template <class K, class V>
struct iteratorM {
  node<K, V>* ver;
public:
  iteratorM() {ver = nullptr; }
  iteratorM(node <K, V>* a) {
    ver = a;
  }
  node<K, V>& operator*() {
    return *ver;
  }
  node <K, V>* operator->() {
    return ver;
  }
  operator bool() {
    return (ver);
  }
 
  static node<K, V>* minOfSubtree(node<K, V>* root) {
    while(root && root->left) root = root->left;
    return root;
  }
  static node<K, V>* maxOfSubtree(node<K, V>* root) {
    while(root && root->right) root = root->right;
    return root;
  }
 
  iteratorM <K, V> operator--(int) {
    if (!ver) return *this;
    if (ver->left) {
      ver = ver->left;
      return iteratorM(ver = maxOfSubtree(ver));
    }
    auto last = ver;
    ver = ver->anc;
    while(ver && ver->left == last) {
      last = ver;
      ver = ver->anc;
    }
    return *this;
  }
  iteratorM <K, V> operator++(int) {
    if (!ver) return *this;
    if (ver->right) {
      ver = ver->right;
      return iteratorM(ver = minOfSubtree(ver));
    }
 
    auto last = ver;
    ver = ver->anc;
    while(ver && ver->right == last) {
      last = ver;
      ver = ver->anc;
    }
    return *this;
  }
};
 
template <class K, class V>
class map {
  node <K, V>* root = nullptr;
  int sz = 0;
  node<K, V>* findNode(K key, bool returnLast = false) {
    auto cur = root;
    auto last = root;
    while(cur && cur->GetKey() != key) {
      last = cur;
      if (key < cur->GetKey())
        cur = cur->left; else
        cur = cur->right;
    }
    if (returnLast && !cur) return last;
    return cur;
  }
public:
  map() = default;
  ~map() {
    //clean();
  }
  void insert(K key, V name) {
    if (!root) {
      root = new node<K, V>(key, name);
      ++sz;
      return;
    }
    auto cur = root;
    auto last = cur;
    while (cur && cur->GetKey() != key) {
      last = cur;
      if (key < cur->GetKey()) cur = cur->left; else
                               cur = cur->right;
    }
    if (cur == nullptr) {
      cur = new node<K, V>(key, name);;
      ++sz;
    } else {
      cur->value = name;
      return;
    }
    if (key < last->GetKey())
      last->left = cur; else
      last->right = cur;
    cur->anc = last;
  }
 
  bool erase(K key) {
    node<K, V>* cur = findNode(key);
    if (cur && cur->GetKey() == key) {
      auto newTree = merge(cur->left, cur->right);
      --sz;
      if (cur == root) {
        root = newTree;
        if (root)
          root->anc = nullptr;
      } else {
        if (cur->anc->left == cur)
          cur->anc->left = newTree; else
          cur->anc->right = newTree;
        if (newTree) newTree->anc = cur->anc;
      }
      delete cur;
      return true;
    }
    return false;
  }
  node<K, V>*  merge(node <K, V>* x, node <K, V>* y) {
    if (!x) return y;
    if (!y) return x;
    if (rand() % 2) {
      y->left = merge(x, y->left);
      if (y->left) y->left->anc = y;
      return y;
    } else {
      x->right = merge(x->right, y);
      if (x->right) x->right->anc = x;
      return x;
    }
  }
  bool inline erase(iteratorM<K, V> x) {
    std::cout << 5 / 0;
  }
 
  iteratorM<K, V> find(K key, bool returnLast = false) {
    return findNode(key, returnLast);
  }
 
  iteratorM<K, V> findOrNext(K key) {
    auto iter = find(key, true);
    if (iter) {
      if (iter.ver->GetKey() < key) iter++;
    }
    return iter;
  }
 
  iteratorM<K, V> begin() {
    auto useless = iteratorM<K, V>();
    return iteratorM<K, V>(useless.minOfSubtree(root));
  }
  iteratorM<K, V> end() {
    auto useless = iteratorM<K, V>();
    return iteratorM<K, V>(useless.maxOfSubtree(root));
  }
 
  void print() {
    auto first = begin();
    if (!first) {
      //assert(sz == 0);
      std::cout << "EMPTY\n";
      return;
    }
    while(first) {
      std::cout << *first;
      first++;
    }
  }
  void print(K item1, K item2) {
    iteratorM<K,V> first = findOrNext(item1);
    while(first && first.ver->GetKey() <= item2) {
      std::cout << *first;
      first++;
    }
  }
  inline int size() { return sz; }
  void clean() {
    clean(root);
    root = nullptr;
    sz = 0;
  }
  void clean(node<K, V>* v) {
    if (!v) return;
    clean(v->left);
    clean(v->right);
    delete v;
  }
  V& operator[](K key) {
    node<K, V>* result = findNode(key);
    if (!result) {
      insert(key, V());
      result = findNode(key);
    }
    return result->value;
  }
};
 
#endif //SATORI_MP_SOLUTION_H
