#ifndef PLATFORMERSFML_GEM_H
#define PLATFORMERSFML_GEM_H

#include "GameObject.h"

class Gem: public GameObject
{
 public:
  Gem();
  ~Gem();


  int positions[5][2] = {{1200,500},{2150,200},{3750,30},
                          {2150,500},{4700,500}};
  sf::Clock fade_clock;
  bool fading = false;
  int alpha = 255;
  void fade_out();
  void gem_init(int x);
  int gem_bounce;
  void bounceFunction(int gem_counter, float dt);
};

#endif // PLATFORMERSFML_GEM_H
