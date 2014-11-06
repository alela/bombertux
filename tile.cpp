#include "tile.h"


sf::Texture Tile::texture;
sf::Sprite Tile::sprite;
    
void Tile::init(){
  Tile::texture.loadFromFile("resources/tiletextures.png");
  Tile::sprite.setTexture(texture);
}

Tile::Tile(int _x, int _y, int _w, int _h, int _type, 
     collision_effect_t _collision_effect): x(_x), y(_y), w(_w), h(_h), 
    type(_type), collision_effect(_collision_effect){}
