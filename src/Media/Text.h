#ifndef PLATFORMERSFML_TEXT_H
#define PLATFORMERSFML_TEXT_H
#include <SFML/Graphics.hpp>

class Text
{
 public:
  sf::Text menu_text;
  sf::Text game_over_text;
  sf::Text game_won_text;
  sf::Text pause_text;
  sf::Text control_tutorial;
  sf::Text obstacle_tutorial;
  sf::Text score_text;

  void init_text(float half_window);

 private:
  sf::Font font;

};

#endif // PLATFORMERSFML_TEXT_H
