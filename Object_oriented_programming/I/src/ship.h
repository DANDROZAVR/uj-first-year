#ifndef PO10_SHIP_HEADER
#define PO10_SHIP_HEADER

#include <istream>
#include <vector>
#include <iostream>
#include "galaxy.h"

class Ship {
  public:
    virtual void setPath(std::istream& in);
    virtual Galaxy::Starsystem* start(Galaxy* g);
    virtual Galaxy::Starsystem* advance();
    virtual ~Ship();
    virtual Galaxy::Starsystem* getStar() {
      return actual;
    }
    bool endWay();
  public:
    std::vector <int> moves;
    size_t stars;
    int start_star, actual_idx;
    Galaxy::Starsystem* actual = nullptr;
    Galaxy* our_galaxy = nullptr;
};

class Hero : public Ship {
public:
  //using Ship::endWay, Ship::start, Ship::advance, Ship::setPath;
  Hero() : Ship(){};
};
class Reaper : public Ship {
public:
  //using Ship::endWay, Ship::start, Ship::advance, Ship::setPath;
  Reaper() : Ship(){};
};


#endif

