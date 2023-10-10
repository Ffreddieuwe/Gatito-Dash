#ifndef PLATFORMERSFML_PLATFORMS_H
#define PLATFORMERSFML_PLATFORMS_H

#include "Enemy.h"

class Platforms: public GameObject
{
 public:
  bool player_on;

  void enemyCollision(Enemy &enemy);
  void playerCollision(Player &player, bool& key_pressed, float ground_level);
  void positionSet(int platform_number);
  float positions[12][2] = {{1400,600},{1700,500},
                             {2100,400},{2550,500},
                             {3400,600},{3700,400},
                             {3400,200},{3700,80}};

};

#endif // PLATFORMERSFML_PLATFORMS_H
