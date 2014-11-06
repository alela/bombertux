#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>
#include "player.h"

class Bonus
{

  int x,y,w,h,tile,type;
  

  sf::Texture texture;
  sf::Sprite sprite;

public:
  Bonus() = default;
  Bonus(int _x, int _y, int tile);
  ~Bonus() = default;
  
  void choose_bonus_type();
  void init();

  sf::Sprite get_sprite() {return sprite;}
  int get_tile(){return tile;}
  int get_type(){return type;}
  
  void set_bonus(std::shared_ptr<Player> player);

};

#endif
