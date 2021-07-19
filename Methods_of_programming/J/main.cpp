#include <iostream>
 
class hashElement {
  unsigned int hashcode = 0;
  std::string val;
  unsigned int smallKey = 0;
  char status = 1;
  int M1 = (int)(1e9 + 107);
public:
  hashElement() = default;
  hashElement(std::string key, std::string value, int p, int p2) {
    this->val = std::move(value);
    setOccupied();
    calcHash(key, p, p2);
  }
  void calcHash(std::string &s, int p, int p2) {
    hashcode = smallKey = 1;
    for (char element : s) {
      hashcode = hashcode * p + element;
      smallKey = (1ll * smallKey * p2) % M1 + (element == '.' ? 1 : element - 'a' + 1);
    }
  }
  unsigned int getHash() const { return hashcode; }
  std::string getValue() const { return val; }
  unsigned int getSmallKey() const { return smallKey; }
  bool equal(hashElement &another) const {
    if (hashcode != another.getHash() || getSmallKey() != another.getSmallKey()) return false;
    return true;
  }
  bool isEmpty() const { return status == 1; }
  bool isCanceled() const { return status == 2; };
  void setEmpty() { status = 1; }
  void setValue(std::string s) { val = std::move(s); }
  void setCanceled() { status = 2; }
  void setOccupied() { status = 0; }
};
 
class hashMap {
  const int p = 29, p2 = 31, m2 = (int)(1e9) + 107;
  hashElement* a = nullptr;
  int sz, empty;
  void resize() {
    if (empty <= sz * 0.4)
      resize(nextPrime(sz * 2 ));
  }
  int nextPrime(int number) const {
    for (int i = number + 1; ; ++i) {
      if (i == p) continue;
      bool prime = true;
      for (int j = 2; j * j <= i; ++j)
        if (i % j == 0) {
          prime = false;
          break;
        }
      if (prime) return i;
    }
  }
  void add(hashElement* b, hashElement item) {
    int index = findEmptyPlace(b, item);
    if (b[index].isEmpty()) --empty;
    b[index].setOccupied();
    if (item.equal(b[index])) {
      b[index].setValue(item.getValue());
      return;
    }
    b[index] = item;
    resize();
  }
  void add(hashElement &item) {
    add(a, item);
  }
  int findEmptyPlace(hashElement* arr, hashElement &item) {
    int index = (item.getHash() ^ item.getSmallKey()) % sz;
    auto res = arr[index];
    int last = -1;
    while(!arr[index].isEmpty() && !item.equal(arr[index])) {
      ++index;
      if (arr[index].isCanceled()) {
        last = index;
      }
      if (index == sz) index = 0;
    }
    if (last != -1 && !item.equal(arr[index]))
      return last;
    return index;
  }
  void resize(int newSize) {
    auto b = new hashElement[newSize];
    empty = newSize;
    int oldSize = sz;
    sz = newSize;
    for (int i = 0; i < oldSize; ++i)
      if (!a[i].isEmpty() && !a[i].isCanceled())
        add(b, hashElement(a[i]));
    delete[] a;
    a = b;
  }
public:
 
 
  ~hashMap() { delete[] a; }
  hashMap() {
    sz = empty = 0;
    resize(29);
  }
  void insert(std::string key, std::string value) {
    hashElement item = hashElement(std::move(key), std::move(value), p, p2);
    add(item);
  }
  std::string find(std::string key) {
    hashElement item = hashElement(std::move(key), "", p, p2);
    int index = findEmptyPlace(a, item);
    if (a[index].isCanceled() || !item.equal(a[index])) return "ERROR";
    return a[index].getValue();
  }
  std::string erase(std::string key) {
    hashElement item = hashElement(std::move(key), "", p, p2);
    int index = findEmptyPlace(a, item);
    if (a[index].isCanceled() || a[index].isEmpty() || !item.equal(a[index])) return "ERROR";
    a[index].setCanceled();
    return a[index].getValue();
  }
};
 
struct Solver {
  static void Solve() {
    int n;
    std::cin >> n;
    hashMap mp;
    while(n--) {
      std::string q, key, val;
      std::cin >> q >> key;
      if (q == "INSERT") {
        std::cin >> val;
        mp.insert(key, val);
      } else
      if (q == "FIND") {
        std::cout << mp.find(key) << '\n';
      } else {
        std::cout << mp.erase(key) << '\n';
      }
    }
 
  }
};
 
#include <unordered_map>
struct Bruter {
  static void Brute() {
    int n;
    std::cin >> n;
    std::unordered_map < std::string, std::string > mp;
    while(n--) {
      std::string q, key, val;
      std::cin >> q >> key;
      if (q == "INSERT") {
        std::cin >> val;
        mp[key] = val;
      } else
      if (q == "FIND") {
        if (mp.find(key) == mp.end())
          std::cout << "ERROR\n"; else
          std::cout << mp[key] << '\n';
      } else {
        if (mp.find(key) == mp.end())
          std::cout << "ERROR\n";
        else {
          std::cout << mp[key] << '\n';
          mp.erase(key);
        }
      }
    }
  }
};
 
#include <chrono>
#include <iostream>
#include <random>
std::mt19937 Gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
std::string func(int cn, int len) {
  std::string res;
  for (int i = 0; i < len; ++i)
    res += char(Gen() % cn + 'a');
  return res;
}
 
void gen() {
  freopen("input.txt", "w", stdout);
  int n = Gen() % 400;
  std::cout << 1 << " " << n << '\n';
  const int cn = 26;
  const int len = 1;
  while(n--) {
    int z = (Gen() % 3);
    if (z == 0) { // FIND
      std::cout << "FIND " << func(cn, 1) << '\n';
    } else
    if (z == 1) { // DELETE
      std::cout << "DELETE " << func(cn, 1) << '\n';
    } else {
      std::cout << "INSERT " << func(cn, 1) << " " << func(cn, 3) << '\n';
    }
  }
}
 
int main() {
  int z;
#ifdef Estb_probitie
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
 
  std::cin >> z;
  while(z--) {
    Solver::Solve();
  }
//  exit(0);
//  std::cin >> z;
//  if (z < 0)z = 0;
//  while(z--) {
//    Bruter::Brute();
//  }
  /*
   for (int i = 0; i < key.size(); ++i)
 
   */
}
