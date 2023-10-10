#ifndef PLATFORMERSFML_TILEMAP_H
#define PLATFORMERSFML_TILEMAP_H

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
 public:
  void create();

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::VertexArray vertices;
  sf::Texture tileset;

  int width;
  int height;
  int tile_size = 32;
};

#endif // PLATFORMERSFML_TILEMAP_H
