#ifndef FIRE_H
#define FIRE_H

#include <SFML/Graphics.hpp>
#include <ctime>

class Fire
{
  double timer;
  sf::Clock fire_timer;

  int tile;
  const int height;
  const int width;

  static sf::Texture texture;
  sf::Sprite sprite;

public:
  Fire() = default;
  ~Fire() = default;

  Fire(int, int, int, int, int);
  
  static void init();
  sf::Sprite get_sprite() {return sprite;}
  
  int get_tile(){return tile;}

  bool done_burning();
};

#endif
