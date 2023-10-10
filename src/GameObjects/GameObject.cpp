#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject()
{
  sprite = NULL;
  delete sprite;
}


void GameObject::initSprite(std::string filename, sf::IntRect size)
{
  sprite = &tempSprite;
  texture.loadFromFile(filename);
  sprite->setTexture(texture);
  sprite->setTextureRect(size);
}

void  GameObject::initObject(std::string filename)
{
  sprite = &tempSprite;
  texture.loadFromFile(filename);
  sprite->setTexture(texture);
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

bool GameObject::isInside(sf::Vector2f click)
{
  if (sprite->getPosition().x < click.x &&
      click.x < sprite->getPosition().x+sprite->getGlobalBounds().width)
  {
    if (sprite->getPosition().y < click.y &&
        click.y < sprite->getPosition().y + sprite->getGlobalBounds().height)
    {
      return true;
    }
  }
  return false;
}