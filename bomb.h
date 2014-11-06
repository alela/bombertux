#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <ctime>
#include "player.h"
#include "fire.h"

class Bomb
{
  int timer;

  sf::Clock bomb_clock;
  bool in_fire;
  int explosion_range;

  int tile;
  const int height;
  const int width;

  static sf::Texture texture;
  sf::Sprite sprite;

  std::shared_ptr<Player> m_owner;

public:
  Bomb();
  Bomb(int _range, int x, int y, int tile, std::shared_ptr<Player> owner);
  ~Bomb() = default;
  static void init();

  sf::Sprite get_sprite() {return sprite;}

  bool is_exploding();
  void set_on_fire(){in_fire = true;}

  int get_range(){return explosion_range;}
  int get_tile(){return tile;}
  
};

#endif
