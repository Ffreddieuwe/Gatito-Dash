#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "GameObject.h"
#include "Gem.h"

class Player: public GameObject
{
 public:
  Player();
  ~Player();

  bool flipped;
  Vector player_vector;
  int hp;
  int score;
  bool airborne;
  int texture_select;
  int frame_select;
  sf::Clock clock1;
  bool on_platform;
  bool halted;
  bool OOB;
  float width;

  float velocityY = 0;
  float jump_start = 1000;

  void outOfBounds(float houseX, float castleX);
  void runAnimation();
  void landingCheck();
  void jumpEnd(bool &key_pressed);
  void playerInit(bool in_menu);
  bool gemCollision(Gem gem);

  //Filenames of sprite sheets
  std::string player_textures[6] = {"Data/Images/Meow Knight/Meow-Knight_Idle.png",
                                   "Data/Images/Meow Knight/Meow-Knight_Run.png",
                                   "Data/Images/Meow Knight/Meow-Knight_Jump.png",
                                   "Data/Images/Meow Knight/Meow-Knight_Take_Damage.png",
                                   "Data/Images/Meow Knight/Meow-Knight_Death.png"};

  //Sizes of sprites on sprite sheets
  sf::IntRect texture_sizes[5] = {sf::IntRect(0,0,
                                               16,16),
                                   sf::IntRect(0,0,
                                               18,18),
                                   sf::IntRect(0,0,
                                               16,18),
                                   sf::IntRect(0,0,
                                               16,16),
                                   sf::IntRect(0,0,
                                               25,16)};

  //Amount of frames for each animation
  int frames[5] = {6,8,12,3,6};

  //Distance between sprites on sprite sheet
  int steps[5][12] = {{26,26,26,26,26,26},
                       {26,41,26,26,26,41,26},
                       {26,26,26,42,42,
                         42,42,26,26,26,26},
                       {26,26},
                       {26,26,26,26,26}};
};

#endif // PLATFORMERSFML_PLAYER_H
