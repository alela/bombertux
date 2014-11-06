#include "player.h"
#include  <cmath>
#include <iostream>

Player::Player(): name("Default"), lifes(3), bomb_ammo(1), bomb_range(3), can_kick_bomb(false), 
		  height(32), width(32), moving_right(0), moving_left(0), 
		  moving_up(0), moving_down(0),
		  dropping_bomb(false), drop_cooldown(500)
{
  texture.loadFromFile("resources/tux.png", sf::IntRect(0, 0, 32, 32));
  sprite.setTexture(texture);
}

Player::Player(std::string _name, int _x, int _y): name(_name), lifes(3), bomb_ammo(1), 
						   bomb_range(3), can_kick_bomb(false),
						   height(32), width(32), 
						   moving_right(0), moving_left(0), 
						   moving_up(0), moving_down(0),
						   dropping_bomb(false), drop_cooldown(500) {

  texture.loadFromFile("resources/"+_name+".png", sf::IntRect(0, 0, 32, 32));
  sprite.setTexture(texture);
  sprite.setPosition(_x, _y);
  
}

void Player::set_tile(int x, int y){
  tile = std::floor((y + 16)/TILE_HEIGHT) * (WINDOW_WIDTH/TILE_WIDTH) 
    + std::floor((x + 16)/TILE_WIDTH);
}

void Player::set_x(int x){
  int y = sprite.getPosition().y;
  sprite.setPosition(x, y);

  set_tile(x, y);
}

void Player::set_y(int y){
  int x = sprite.getPosition().x;
  sprite.setPosition(x, y);

  set_tile(x, y);
}

void Player::drop_bomb(){
  dropping_bomb = false;
  bomb_ammo--;
}


bool Player::is_dropping_bomb(){
  bool ret_val = (bool)dropping_bomb;
  dropping_bomb = false;
  return ret_val;
}


void Player::decrement_life(){
  sf::Time time = fire_cooldown.getElapsedTime();
  if(time.asMilliseconds() >= 1000){
    lifes--;
    fire_cooldown.restart();
  }    
}
