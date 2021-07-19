#include <iostream>
#include <algorithm>
#include <vector>
 
 
struct Solver {
  int n;
  std::string order1, order2, order3;
  std::vector < int > a, b, depth, father, lChild, rChild, placea, placeb;
  std::vector < char > type;
  std::vector <int> orderOfNodes;
  void compress(int n, std::vector < int > &a) {
    std::pair <int, int> asort[n];
    for (int i = 0; i < n; ++i)
      asort[i] = {a[i], i};
    std::sort(asort, asort + n);
    for (int i = 0; i < n; ++i)
      a[asort[i].second] = i;
  }
  Solver() {
    std::cin >> n;
    a.resize(n);
    b.resize(n);
    depth.resize(n);
    father.resize(n);
    lChild.resize(n);
    rChild.resize(n);
    placea.resize(n);
    placeb.resize(n);
    type.resize(n);
 
    std::cin >> order1;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::cin >> order2;
    for (int i = 0; i < n; ++i) std::cin >> b[i];
 
    if ((order1 == "POSTORDER" && order2 == "PREORDER") || (order1 == "INORDER")){
      swap(order1, order2);
      swap(a, b);
    }
    // order1 = PREORDER AND order2 = POSTORDER
    // OR
    // order1 = POSTORDER/PREORDER AND order2 = INORDER
    if (order1 == "PREORDER") {
      if (order2 == "INORDER") order3 = "POSTORDER"; else order3 = "INORDER";
    } else order3 = "PREORDER";
    compress(n, a);
    compress(n, b);
    for (int i = 0; i < n; ++i)
      placea[a[i]] = i;
    for (int i = 0; i < n; ++i)
      placeb[b[i]] = i;
  }
  void inorder(int lInorder, int rInorder, int lOther, int rOther, int lev = 0, bool lChild = false, bool rChild = false, int pr = -1) {
    if (lOther > rOther || lInorder > rInorder) exit(1);
    char name = 'K';
    if (lChild) name = 'L';
    if (rChild) name = 'R';
 
    int v = -1, placeInorder;
    if (order1 == "PREORDER")  v = a[lOther++], placeInorder = placeb[v];
    if (order1 == "POSTORDER") v = a[rOther--], placeInorder = placeb[v];
    father[v] = pr;
    depth[v] = lev;
    type[v] = name;
 
    if (placeInorder != lInorder) {
      int newrOther = lOther + placeInorder - lInorder - 1;
      inorder(lInorder, placeInorder - 1, lOther, newrOther, lev + 1, true, false, v);
    }
    if (placeInorder != rInorder) {
      int newlOther = rOther - (rInorder - placeInorder) + 1;
      inorder(placeInorder + 1, rInorder, newlOther, rOther, lev + 1, false, true, v);
    }
  }
  bool prepostorder(int lpreOrder, int rpreOrder, int lpostOrder, int rpostOrder, int lev = 0, bool lChild = false, bool rChild = false, int pr = -1) {
    if (lpreOrder > rpreOrder || lpostOrder > rpostOrder) exit(1);
    char name = 'K';
    if (lChild) name = 'L';
    if (rChild) name = 'R';
    int v = a[lpreOrder++];
    father[v] = pr;
    depth[v] = lev;
    type[v] = name;
    if (lpreOrder > rpreOrder) return true;
    if (a[lpreOrder] == b[--rpostOrder]) return false;
    if (!prepostorder(lpreOrder, placea[b[rpostOrder]] - 1, lpostOrder, placeb[a[lpreOrder]], lev + 1, true, false, v)) return false;
    if (!prepostorder(placea[b[rpostOrder]], rpreOrder, placeb[a[lpreOrder]] + 1, rpostOrder, lev + 1, false, true, v)) return false;
    return true;
  }
  void numerate(int v) {
    if (order3 == "PREORDER") {
      orderOfNodes.push_back(v);
      if (lChild[v] != -1) numerate(lChild[v]);
      if (rChild[v] != -1) numerate(rChild[v]);
    } else if (order3 == "INORDER") {
      if (lChild[v] != -1) numerate(lChild[v]);
      orderOfNodes.push_back(v);
      if (rChild[v] != -1) numerate(rChild[v]);
    } else {
      if (lChild[v] != -1) numerate(lChild[v]);
      if (rChild[v] != -1) numerate(rChild[v] );
      orderOfNodes.push_back(v);
    }
  }
public:
  void Solve() {
    if (order2 == "INORDER" || order1 == "INORDER")
      inorder(0, n - 1, 0, n - 1); else
    if (!prepostorder(0, n - 1, 0, n - 1)) {
      std::cout << "ERROR\n";
      return;
    }
    std::fill(lChild.begin(), lChild.end(), -1);
    std::fill(rChild.begin(), rChild.end(), -1);
    int root = -1;
    for (int i = 0; i < n; ++i)
      if (father[i] == -1) root = i; else {
        if (type[i] == 'L')
          lChild[father[i]] = i; else
          rChild[father[i]] = i;
      }
    numerate(root);
    for (int i : orderOfNodes)
      std::cout << depth[i] << " ";
    std::cout << '\n';
    for (int i : orderOfNodes)
      std::cout << type[i] << " ";
    std::cout << '\n';
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
