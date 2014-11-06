#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "player.h"
#include "bomb.h"
#include "bonus.h"
#include "fire.h"
#include "tile.h"
#include <vector>
#include <map>
#include <memory>
#include <set>

class Collision_handler
{
  Player* player;
  std::vector<std::shared_ptr<Player>>* m_players;
  std::vector<std::shared_ptr<Bomb>>* m_bombs;
  std::vector<std::shared_ptr<Bonus>>* m_bonuses;
  std::vector<std::shared_ptr<Tile>>* m_tiles;
  
  std::shared_ptr<Tile> get_tile(int x, int y);
  std::set<int> get_tiles_index(int x, int y);
  bool blocked_tile(int tile);
  
  std::vector<unsigned int> check_fire_horizontal(int fire_tile, int range);
  std::vector<unsigned int> check_fire_verticaly(int fire_tile, int range);
  
public:
  Collision_handler() = default;
  Collision_handler(std::vector<std::shared_ptr<Player>>*,
		    std::vector<std::shared_ptr<Bomb>>*,
		    std::vector<std::shared_ptr<Bonus>>*,
		    std::vector<std::shared_ptr<Tile>>*);

  ~Collision_handler() = default;

  void set_pos(std::shared_ptr<Player>&);
  std::vector<unsigned int> get_fire_pos(int fire_tile, int range);
  
  bool fire_hit_player(std::shared_ptr<Player>&, std::vector<std::shared_ptr<Fire>>&);
  bool fire_hit_bomb(std::shared_ptr<Bomb>&, std::vector<std::shared_ptr<Fire>>&);
  std::vector<int> fire_hit_breakable(std::vector<std::shared_ptr<Fire>>&);

  bool is_bomb_on_tile(int tile);
};

#endif
