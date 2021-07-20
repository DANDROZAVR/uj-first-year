#include <istream>
#include <iostream>
#include <unordered_set>
#include "main.h"

Galaxy& Galaxy::load(std::istream& in) {
  in >> system_cnt >> target_idx;
  ban.resize(system_cnt);
  systems.reserve(system_cnt);
  for (int index = 0; index < system_cnt; ++index) {
    Starsystem* next_star = new Starsystem();
    next_star->setId(index);
    systems.push_back(next_star);
    next_star->load(this, in);
  }
  target = systems[target_idx]; // possible error
  return *this;
}

Galaxy::Starsystem& Galaxy::Starsystem::load(Galaxy* g, std::istream& in) {
  in >> stars;
  edges.reserve(stars);
  for (int index = 0; index < stars; ++index) {
    int stop;
    std::cin >> stop;
    edges.push_back(stop);
  }
  our_galaxy = g;
  return *this;
}

Galaxy::Starsystem* Galaxy::Starsystem::adjacent(size_t idx) {
  if (idx < 0 || idx >= stars) return nullptr;
  return our_galaxy->systems[edges[idx]];
}

bool Galaxy::Starsystem::isTarget() {
  return our_galaxy->target == this;
}

Galaxy& Galaxy::add(Reaper* r) {
  enemies.push_back(r);
  return *this;
}
Galaxy& Galaxy::add(Hero* r) {
  hero = r;
  return *this;
}

Galaxy::Starsystem* Galaxy::getSystem(size_t idx) {return systems[idx];}

Result Galaxy::simulate() {
  for (int i : visited)
    ban[i] = false;
  visited.clear();
  for (Reaper* boss : enemies) {
    int id = boss->start(this)->getId();
    if (!ban[id]) {
      ban[id] = true;
      visited.push_back(id);
    }
  }

  if (ban[hero->start(this)->getId()])
    return Result::Failure;
  if (hero->getStar()->isTarget())
    return Result::Success;
  while(!hero->endWay()) {
    for (auto boss : enemies) {
      int id = boss->advance()->getId();
      if (!ban[id]) {
        ban[id] = true;
        visited.push_back(id);
      }
    }

    auto star = hero->advance();
    if (star == nullptr)
      return Result::Invalid;
    if (star->isTarget())
      return Result::Success;
    if (ban[star->getId()])
      return Result::Failure;
  }
  return Result::Invalid;
}

Galaxy::~Galaxy() {
  for (auto boss : enemies)
    delete boss;
  delete hero;
  for (auto star : systems)
    delete star;
};

