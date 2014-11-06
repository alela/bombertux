#include "bomb.h"
#include <iostream>


sf::Texture Bomb::texture;

void Bomb::init(){
  Bomb::texture.loadFromFile("resources/bomb.png", sf::IntRect(0, 0, 32, 32));
}

Bomb::Bomb(int _range, int x, 
	   int y, int _tile,
	   std::shared_ptr<Player> owner): timer(3), in_fire(false), 
					   explosion_range(_range), tile(_tile), 
					   height(32), width(32), 
					   m_owner(owner){

  sprite.setTexture(Bomb::texture);
  sprite.setPosition(x, y);
  
}

bool Bomb::is_exploding(){
  sf::Time time = bomb_clock.getElapsedTime();
  bool is_time_to_explode = (time.asSeconds() >= timer) || in_fire;

  if(is_time_to_explode){
    m_owner->increment_bomb_ammo();
  }
  
  return is_time_to_explode;
}



