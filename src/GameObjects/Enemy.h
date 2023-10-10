#ifndef PLATFORMERSFML_ENEMY_H
#define PLATFORMERSFML_ENEMY_H

#include "Player.h"

class Enemy: public GameObject
{
 public:
  Enemy();
  ~Enemy();

  void runAnimation();
  bool playerCollision(Player player);
  void Patrol(float dt);
  void enemyInit();

  int hp;
  bool flipped;
  int texture_select;
  int frame_select;
  sf::Clock clock;
  float patrol_start = 4200;
  float patrol_end = 4900;
  Vector vector;

  std::string enemy_textures[2] = {"Data/Images/Chick-Boy Free Pack/ChikBoy_idle.png",
                                    "Data/Images/Chick-Boy Free Pack/ChikBoy_run.png"};

  //Sizes of sprites on sprite sheets
  sf::IntRect texture_sizes[2] = {sf::IntRect(0,0,32,32),
                                   sf::IntRect(0,0,32,32)};

  //Amount of frames for each animation
  int frames[2] = {6,10};
};

#endif // PLATFORMERSFML_ENEMY_H
