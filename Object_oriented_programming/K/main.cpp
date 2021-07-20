#ifndef _POLABSCPP_BFS_H
#define _POLABSCPP_BFS_H
 
#include <functional>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
 
std::function<int(std::vector<int>::iterator, std::vector<int>::iterator)> make_bfs(
    std::function<std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(int)> getEdges,
    std::function <void(int)> func) {
  return [getEdges, func](std::vector<int>::iterator start, std::vector<int>::iterator end) {
    std::queue<int> q;
    std::unordered_set <int> used;
    while(start != end) {
      q.push(*start);
      used.insert(*start);
      ++start;
    }
    while(!q.empty()) {
      int v = q.front();
      func(v);
      q.pop();
      auto res = getEdges(v);
      auto from = res.first, to = res.second;
      while(from != to) {
        auto& elem = *from;
        if (!used.count(elem)) {
          used.insert(elem);
          q.push(elem);
        }
        ++from;
      }
    }
    return used.size();
  };
}
 
 
#endif //_POLABSCPP_BFS_H
