#include "fire.h"
#include <iostream>

sf::Texture Fire::texture;

void Fire::init(){
  Fire::texture.loadFromFile("resources/fire.png", sf::IntRect(0, 0, 32, 32));
}

Fire::Fire(int x, int y, int h, int w, int t) : height(h), width(w),  
						tile(t), timer(1){

  sprite.setTexture(Fire::texture);
  sprite.setPosition(x, y);
}

bool Fire::done_burning(){
  sf::Time counter = fire_timer.getElapsedTime();
  return counter.asSeconds() >= timer;
}
