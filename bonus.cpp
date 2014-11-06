#include "bonus.h"
#include <vector>
#include <string>
#include <random>
#include <ctime>

Bonus::Bonus(int _x, int _y, int _tile):x(_x), y(_y), tile(_tile){

  choose_bonus_type();
  init();
  
}


void Bonus::choose_bonus_type(){
  std::default_random_engine generator; 
  std::uniform_int_distribution<int> distribution(-5,1);
  
  generator.seed(std::clock());
  type = distribution(generator); 
}


void Bonus::init(){
  if(type <= -1)
    return ;
  
  std::vector<std::string> images{"resources/bomb2.png", "resources/fire3.png"};
  texture.loadFromFile(images[type], sf::IntRect(0, 0, 32, 32));  
  sprite.setTexture(texture);
  sprite.setPosition(x,y);    
}

void Bonus::set_bonus(std::shared_ptr<Player> player){
  
  typedef void (Player::*fun)();
  std::vector<fun>bonuses {&Player::increment_bomb_ammo, 
      &Player::increment_bomb_range};
  
  ((*player).*bonuses[type])();
}
