#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <ctime>
#include "constants.h"
#include <string>

class Player 
{
  std::string name;
  int lifes;
  
  int bomb_ammo;
  int bomb_range;
  bool can_kick_bomb;
  
  bool fire_resistent;
  sf::Clock fire_cooldown;
  void fire_resistent_cooldown();

  int tile;

  const int height;
  const int width;

  std::map<sf::Keyboard::Key, int*> move_controlls;
  std::map<sf::Keyboard::Key, int*> action_controlls;

  //states
  int moving_up;
  int moving_down;
  int moving_right;
  int moving_left;

  //actions
  int dropping_bomb;
  int drop_cooldown;

  sf::Texture texture;
  sf::Sprite sprite;

  friend class Input_handler;

  void set_tile(int x, int y);

public:
  Player();
  Player(std::string _name, int _x, int _y);
  ~Player() = default;
   
  sf::Sprite get_sprite() {return sprite;}
  int get_x(){return sprite.getPosition().x;}
  int get_y(){return sprite.getPosition().y;}
  int get_tile(){return tile;}
  int get_bomb_range() {return bomb_range;}
  int get_ammo(){return bomb_ammo;}
  int get_lifes(){return lifes;}
  int get_vertical_movement(){return moving_down - moving_up;}
  int get_horizontal_movement(){return moving_right - moving_left;}
  std::map<sf::Keyboard::Key, int*>& get_mv_ctrls(){return move_controlls;}
  std::map<sf::Keyboard::Key, int*>& get_action_ctrls(){return action_controlls;}
  std::string get_name(){return name;}
  

  void set_x(int x);
  void set_y(int y);
  void increment_bomb_ammo() {bomb_ammo++;} 
  void decrement_bomb_ammo() {bomb_ammo--;}
  void increment_bomb_range() {bomb_range++;}
  bool is_dropping_bomb();
  void drop_bomb();  
  void decrement_life();
  void set_bonus(int bonus_type);  
};

#endif
