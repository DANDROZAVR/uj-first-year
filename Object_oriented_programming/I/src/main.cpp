#include "main.h"
#include <iostream>

int main(int argc, char** argv) {
#ifdef Estb_probitie
  freopen("input.txt", "r", stdin);
#endif
  //std::ios_base::sync_with_stdio(0);
  //std::cin.tie(0);
  //std::cout.tie(0);

  Galaxy galaxy;
  galaxy.load(std::cin);
  size_t rc;
  std::cin >> rc;
  for (size_t i = 0; i<rc; ++i) {
    Reaper* r = new Reaper();
    r->setPath(std::cin);
    galaxy.add(r);
  }
  Hero* h = new Hero();
  h->setPath(std::cin);
  Result r = galaxy.add(h).simulate();
  print_result(r);
  return 0;
}




