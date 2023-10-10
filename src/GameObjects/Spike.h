#ifndef PLATFORMERSFML_SPIKE_H
#define PLATFORMERSFML_SPIKE_H
#include "Player.h"

class Spike: public GameObject
{
 public:
  int positions[4][2] = {{2000,650},{2280,650},{3650,650},{4685,650}};
  bool playerCollision(Player &player);
  void initSpike(int num);
};

#endif // PLATFORMERSFML_SPIKE_H
