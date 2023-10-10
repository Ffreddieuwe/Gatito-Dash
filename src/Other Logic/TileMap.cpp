#include "TileMap.h"

void TileMap::create()
{
  tileset.loadFromFile("Data/Images/Map/TX Tileset Ground.png");

  const int layout[] = {1};
  width = 200;
  height = 1;

  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(width*height*4);

  for (int x = 0; x < width; ++x)
  {
    for (int y = 0; y<height; ++y)
    {
      int tile_across = 1;
      int tile_down = 0;

      sf::Vertex* quad = &vertices[(x + y * width) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(337+(x * tile_size), 695+(y * tile_size));
      quad[1].position = sf::Vector2f(337+((x + 1) * tile_size), 695+(y * tile_size));
      quad[2].position = sf::Vector2f(337+((x + 1) * tile_size), 695+((y + 1) * tile_size));
      quad[3].position = sf::Vector2f(337+(x * tile_size), 695+((y + 1) * tile_size));

      // define its 4 texture coordinates
      quad[0].texCoords = sf::Vector2f(tile_across * tile_size, tile_down * tile_size);
      quad[1].texCoords = sf::Vector2f((tile_across + 1) * tile_size, tile_down * tile_size);
      quad[2].texCoords = sf::Vector2f((tile_across + 1) * tile_size, (tile_down + 1) * tile_size);
      quad[3].texCoords = sf::Vector2f(tile_across * tile_size, (tile_down + 1) * tile_size);
    }
  }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &tileset;

  // draw the vertex array
  target.draw(vertices, states);
}

