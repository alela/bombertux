#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "constants.h"

class Tile
{
public:
  Tile(int _x, int _y, int _w, int _h, int _type, 
       collision_effect_t _collision_effect);
  ~Tile() = default;

  static void init();
  static sf::Texture texture;
  static sf::Sprite sprite;
  
  int x,y,w,h;
  int type;
  collision_effect_t collision_effect;
};

#endif
