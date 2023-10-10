#ifndef PLATFORMERSFML_GAMEOBJECT_H
#define PLATFORMERSFML_GAMEOBJECT_H

#include "../Other Logic/Vector.h"
#include <SFML/Graphics.hpp>
#include <string>

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  void initObject(std::string filename);
  void initSprite(std::string filename, sf::IntRect size);
  bool isInside(sf::Vector2f click);
  sf::Texture texture;

  sf::Sprite* getSprite();

  bool is_visible;

 protected:
  sf::Sprite tempSprite;

  sf::Sprite* sprite = nullptr;


};

#endif // PLATFORMERSFML_GAMEOBJECT_H
