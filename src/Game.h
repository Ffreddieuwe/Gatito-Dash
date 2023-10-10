#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "GameObjects/Platforms.h"
#include "GameObjects/Spike.h"
#include "Media/Audio.h"
#include "Media/Text.h"
#include "Other Logic/TileMap.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void resetButtons();

 private:
  sf::Clock dmg_clock;

  void newRound();

  enum game_state{Menu = 1,Gameplay = 2,Pause = 3, End_Screen = 4};
  game_state current_state;
  sf::RenderWindow& window;
  sf::View player_view;

  TileMap map;

  //Audio
  Audio audio_controller;

  //Text
  Text text_controller;

  //Sprites
  Player player;
  Enemy enemy;
  GameObject house;
  GameObject background;
  GameObject castle;
  Spike spikes[4];

  // GameObjects
  GameObject lives[3];
  int life_counter;
  Platforms platforms[8];
  Gem gems[5];
  int gem_counter;

  //Jump related variables
  float gravity = 0.2f;
  float ground_level;

  //Key handling/click handling variables
  bool key_pressed;
  enum button_pressed{Play_but = 1, Exit_but = 2, Pause_Play_but = 3, Menu_but = 4, None = 5};
  button_pressed pressed;
  GameObject play_button;
  GameObject exit_button;
  GameObject pause_play_button;
  GameObject menu_button;
};

#endif // PLATFORMER_GAME_H
