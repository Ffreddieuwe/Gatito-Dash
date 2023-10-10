#include "Text.h"

void Text::init_text(float half_window)
{
  font.loadFromFile("Data/Fonts/BubblegumSans-Regular.ttf");

  menu_text.setString("Welcome to Gatito Dash!");
  menu_text.setFont(font);
  menu_text.setCharacterSize(60);
  menu_text.setFillColor(sf::Color::Red);
  menu_text.setPosition
    (
      half_window-menu_text.getGlobalBounds().width/2,
      30
    );

  game_over_text.setString("You Lost!\nReturn to the menu\nto play again");
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(30);
  game_over_text.setFillColor(sf::Color::Black);

  game_won_text.setString("You Won!\nReturn to the menu\nto play again");
  game_won_text.setFont(font);
  game_won_text.setCharacterSize(30);
  game_won_text.setFillColor(sf::Color::Yellow);

  pause_text.setString("Game Paused");
  pause_text.setFont(font);
  pause_text.setCharacterSize(35);
  pause_text.setFillColor(sf::Color::Red);

  control_tutorial.setString("Use A and D to move left and right\nTap space to do a short jump\nPress and hold space to do a high jump\n\nCollect all the gems and reach the castle to win!");
  control_tutorial.setFont(font);
  control_tutorial.setCharacterSize(30);
  control_tutorial.setFillColor(sf::Color::Red);
  control_tutorial.setPosition(800,70);

  obstacle_tutorial.setString("Avoid obstacles and enemies\nIf you run out of lives you lose!");
  obstacle_tutorial.setFont(font);
  obstacle_tutorial.setCharacterSize(30);
  obstacle_tutorial.setFillColor(sf::Color::Red);
  obstacle_tutorial.setPosition(2000,100);

  score_text.setString("0");
  score_text.setFont(font);
  score_text.setCharacterSize(30);
  score_text.setFillColor(sf::Color::Red);
  score_text.setPosition(1600,0);
}
