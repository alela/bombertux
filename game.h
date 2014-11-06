#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include "player.h"
#include "collision_handler.h"
#include "input_handler.h"
#include "tile.h"
#include "bonus.h"


class Game
{
  std::vector<std::shared_ptr<Player>> players;
  std::vector<std::shared_ptr<Bomb>> bombs;
  std::vector<std::shared_ptr<Fire>> fire;
  std::vector<std::shared_ptr<Tile>> tiles; 
  std::vector<std::shared_ptr<Bonus>> bonuses; 
  
  std::unique_ptr<Collision_handler> collision_handler;
  std::unique_ptr<Input_handler> input_handler;


  bool init();
  bool read_tiles();
  bool create_players();
 
  bool read_input();
  void place_fire(int, int);
  void do_actions();
  void drop_bomb();
  void delete_bombs();
  void delete_fire();
  void check_fire_collision();
  void tile_to_bonus(int tile);
  void check_bonus_collision();
  void set_pos();
  void remove_dead_ppl();
  void check_for_winner();

  void render_all(sf::RenderWindow&);
  template<typename T>
    void render(sf::RenderWindow&, T drawable);
 
public:
  Game();
  ~Game() = default;
  int run(sf::RenderWindow&);
  
};

template<typename T>
void Game::render(sf::RenderWindow& window, T drawables){
  for(const auto& drawable : drawables){
    window.draw(drawable->get_sprite());
  }
}

#endif
