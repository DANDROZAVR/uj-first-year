#include <bits/stdc++.h>
 
 
struct Solver {
  int n;
  std::vector <int> left, right, people, weight, timeToRoot, peopleToRoot, subtreeSize, orderOfNodes;
  std::vector <bool> centroid;
  std::string order;
  Solver() {
    std::cin >> n;
    left.resize(n);right.resize(n);people.resize(n);weight.resize(n);
    subtreeSize.resize(n);
    timeToRoot.resize(n);
    centroid.resize(n);
    peopleToRoot.resize(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> left[i] >> right[i] >> people[i] >> weight[i];
      --left[i];
      --right[i];
    }
    std::cin >> order;
  }
  void calcTimeToRoot(int v, int colect = 0) {
    colect += weight[v];
    timeToRoot[v] = colect;
    if (left[v] != -1)
      calcTimeToRoot(left[v], colect);
    if (right[v] != -1)
      calcTimeToRoot(right[v], colect);
  }
  int calcPeopleToRoot(int v) {
    int colect = 0;
    if (left[v] != -1)
      colect += calcPeopleToRoot(left[v]);
    if (right[v] != -1)
      colect += calcPeopleToRoot(right[v]);
    peopleToRoot[v] = colect;
    colect += people[v];
    return colect;
  }
  void calcSz(int v) {
    subtreeSize[v] = people[v];
    if (left[v] != -1) {
      calcSz(left[v]);
      subtreeSize[v] += subtreeSize[left[v]];
    }
    if (right[v] != -1) {
      calcSz(right[v]);
      subtreeSize[v] += subtreeSize[right[v]];
    }
  }
  void numerate(int v, int clc = 0) {
    if (order == "PREORDER") {
      orderOfNodes.push_back(v);
      if (left[v] != -1) numerate(left[v], clc);
      if (right[v] != -1) numerate(right[v], clc);
    } else if (order == "INORDER") {
      if (left[v] != -1) numerate(left[v], clc);
      orderOfNodes.push_back(v);
      if (right[v] != -1) numerate(right[v], clc);
    } else {
      if (left[v] != -1) numerate(left[v], clc);
      if (right[v] != -1) numerate(right[v], clc);
      orderOfNodes.push_back(v);
    }
  }
  void checkCentroid(int v) {
    bool good = true;
    if (subtreeSize[0] - subtreeSize[v] > subtreeSize[0] / 2) good = false;
    if (left[v] != -1 && subtreeSize[left[v]] > subtreeSize[0] / 2) good = false;
    if (right[v] != -1 && subtreeSize[right[v]] > subtreeSize[0] / 2) good = false;
    if (left[v] != -1) checkCentroid(left[v]);
    if (right[v] != -1) checkCentroid(right[v]);
    if (good) centroid[v] = true;
  }
public:
  void Solve() {
    calcTimeToRoot(0);
    calcPeopleToRoot(0);
    calcSz(0);
    numerate(0);
    checkCentroid(0);
    int answerCentroid = -1;
    for (int i : orderOfNodes)
      if (centroid[i]) {
        answerCentroid = i;
        break;
      }
    for (int i : orderOfNodes) std::cout << timeToRoot[i] << " "; std::cout << '\n';
    for (int i : orderOfNodes) std::cout << peopleToRoot[i] << " "; std::cout << '\n';
    std::cout << answerCentroid + 1 << '\n';
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
