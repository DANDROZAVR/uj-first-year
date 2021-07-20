#ifndef PO10_GALAXY_HEADER
#define PO10_GALAXY_HEADER

#include "result.h"
#include <istream>
#include <vector>

class Reaper;
class Hero;


class Galaxy {
  public:

  Galaxy& load(std::istream& in);
  Galaxy& add(Reaper* r);
  Galaxy& add(Hero* h);
  Result simulate();

  class Starsystem {
    public:
      Starsystem& load(Galaxy* g, std::istream& in);
      Starsystem* adjacent(size_t idx);
      bool isTarget();
      void setId(int id) {
        system_id = id;
      }
      int getId() { return system_id; }
    private:
      size_t stars;
      int system_id;
      std::vector <int> edges;
      Galaxy* our_galaxy;
  };

  Starsystem* getSystem(size_t idx);

  ~Galaxy();
private:
  size_t system_cnt;
  std::vector <Starsystem*> systems;
  std::vector <Reaper*> enemies;
  std::vector <bool> ban;
  int target_idx;
  Starsystem* target;
  Hero* hero;
  std::vector <int> visited;
};



#endif

