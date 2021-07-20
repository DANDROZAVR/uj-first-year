#include <istream>
#include "ship.h"

void Ship::setPath(std::istream& in) {
  in >> stars;
  in >> start_star;
  moves.reserve(stars - 1);
  for (int index = 1; index < stars; ++index) {
    int k;
    in >> k;
    moves.push_back(k);
  }
}

Galaxy::Starsystem* Ship::start(Galaxy* g) {
  actual = g->getSystem(start_star);
  our_galaxy = g;
  actual_idx = 0;
  return actual;
}

Galaxy::Starsystem* Ship::advance() {
  if (actual_idx + 1 == stars) return actual;
   auto temp = actual->adjacent(moves[actual_idx++]);
   actual = temp;
   return temp;
}

bool Ship::endWay() {
  return actual_idx + 1 == stars;
}

Ship::~Ship() {}

