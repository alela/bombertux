#include "collision_handler.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>


Collision_handler::Collision_handler(std::vector<std::shared_ptr<Player>>* _players,
				     std::vector<std::shared_ptr<Bomb>>* _bombs,
				     std::vector<std::shared_ptr<Bonus>>* _bonuses,
				     std::vector<std::shared_ptr<Tile>>* _tiles)
  :m_players(_players), m_bombs(_bombs), m_bonuses(_bonuses), m_tiles(_tiles){}


std::shared_ptr<Tile> Collision_handler::get_tile(int x_cord, int y_cord){
  int tile = std::floor(y_cord /TILE_HEIGHT) * (WINDOW_WIDTH/TILE_WIDTH) 
    + std::floor(x_cord/TILE_WIDTH);
  return (*m_tiles)[tile];
}


std::set<int> Collision_handler::get_tiles_index(int x_cord, int y_cord){
  std::set<int> adj_tiles;
  
  int topleft = std::floor(y_cord / TILE_HEIGHT) * (WINDOW_WIDTH/TILE_WIDTH) 
    + std::floor(x_cord/TILE_WIDTH);
  int topright = std::floor(y_cord / TILE_HEIGHT) * (WINDOW_WIDTH/TILE_WIDTH) 
    + std::floor((x_cord+PLAYER_WIDTH) / TILE_WIDTH);
  int bottomleft = std::floor((y_cord+PLAYER_WIDTH) / TILE_HEIGHT) * (WINDOW_WIDTH/TILE_WIDTH) 
    + std::floor(x_cord / TILE_WIDTH);
  int bottomright = std::floor((y_cord+PLAYER_WIDTH) / TILE_HEIGHT) * (WINDOW_WIDTH/TILE_WIDTH) 
    + std::floor((x_cord+PLAYER_WIDTH) / TILE_WIDTH);

  adj_tiles.insert(topleft);
  adj_tiles.insert(topright);
  adj_tiles.insert(bottomleft);
  adj_tiles.insert(bottomright);
  
  return adj_tiles;
}


int cord_to_tile(int x, int y){
  return std::floor(y / TILE_HEIGHT) * (WINDOW_WIDTH/TILE_WIDTH) 
    + std::floor(x/TILE_WIDTH);
}


bool Collision_handler::blocked_tile(int tile){
  return (*m_tiles)[tile]->collision_effect != collision_effect_t::TRANSPARENT
    || is_bomb_on_tile(tile);
}


void Collision_handler::set_pos(std::shared_ptr<Player>& player){
  int x = player->get_x() + player->get_horizontal_movement();
  int y = player->get_y() + player->get_vertical_movement();
  
  std::set<int> new_tiles = get_tiles_index(x, player->get_y());
  std::set<int> current_tiles = get_tiles_index(player->get_x(), player->get_y());
  std::set<int> diff;
  std::set<int>::iterator it;
  
  std::set_difference(new_tiles.begin(), new_tiles.end(),
		      current_tiles.begin(), current_tiles.end(),
		      std::inserter(diff, diff.begin()));
  
  it = std::find_if(diff.begin(), diff.end(), 
		    std::bind(&Collision_handler::blocked_tile, *this, std::placeholders::_1));
		    

  if(it == diff.end())
    player->set_x(x);

 
  diff.clear();
  new_tiles = get_tiles_index(player->get_x(), y);
  std::set_difference(new_tiles.begin(), new_tiles.end(),
		      current_tiles.begin(), current_tiles.end(),
		      std::inserter(diff, diff.begin()));
			    
  it = std::find_if(diff.begin(), diff.end(), 
		    std::bind(&Collision_handler::blocked_tile, *this, std::placeholders::_1));
		    

  if(it == diff.end())
    player->set_y(y);
}


std::vector<unsigned int> Collision_handler::check_fire_horizontal(int tile, 
								   int range){
  std::vector<unsigned int> valid_tiles;
  
  //check left
  for(int i = tile; i > tile - range; i--){

    if((*m_tiles)[i]->collision_effect == collision_effect_t::TRANSPARENT)
      valid_tiles.push_back(i);
    else if((*m_tiles)[i]->collision_effect == collision_effect_t::BREAKABLE){
      valid_tiles.push_back(i);
      break;
    }
    else 
      break;
  }
  
  //check right
  for(int i = tile; i < tile + range; i++){
    
    if((*m_tiles)[i]->collision_effect == collision_effect_t::TRANSPARENT)
      valid_tiles.push_back(i);
    else if((*m_tiles)[i]->collision_effect == collision_effect_t::BREAKABLE){
      valid_tiles.push_back(i);
      break;
    }
    else
      break;
  }

  return valid_tiles;
}



std::vector<unsigned int> Collision_handler::check_fire_verticaly(int tile, int range){
  std::vector<unsigned int> valid_tiles;
  int amount_of_tiles = m_tiles->size();
  
  //check upwards
  for(int i = tile; i > tile - (range * TILES_PER_ROW); i -= TILES_PER_ROW){

    if((*m_tiles)[i]->collision_effect == collision_effect_t::TRANSPARENT)
      valid_tiles.push_back(i);
    else if((*m_tiles)[i]->collision_effect == collision_effect_t::BREAKABLE){
      valid_tiles.push_back(i);
      break;
    }
    else
      break;
  }

  //check downwards
  for(int i = tile; i < tile + (range * TILES_PER_ROW); i += TILES_PER_ROW){

    if((*m_tiles)[i]->collision_effect == collision_effect_t::TRANSPARENT)
      valid_tiles.push_back(i);
    else if((*m_tiles)[i]->collision_effect == collision_effect_t::BREAKABLE){
      valid_tiles.push_back(i);
      break;
    }
    else
      break;    
  }

  return valid_tiles;
}



std::vector<unsigned int> Collision_handler::get_fire_pos(int fire_tile, 
							  int range){
  std::vector<unsigned int> valid_tiles = check_fire_horizontal(fire_tile, range);
  std::vector<unsigned int> tmp = check_fire_verticaly(fire_tile, range);
  
  valid_tiles.insert(valid_tiles.begin(), tmp.begin(), tmp.end());  
  return valid_tiles;
}



bool Collision_handler::fire_hit_player(std::shared_ptr<Player>& player, 
					std::vector<std::shared_ptr<Fire>>& fire){

  sf::FloatRect playerbox = player->get_sprite().getGlobalBounds();
  std::vector<std::shared_ptr<Fire>>::iterator it;
  
  it = std::find_if(fire.begin(), fire.end(), 
		    [playerbox](std::shared_ptr<Fire> fire){
		      return playerbox.intersects(fire->get_sprite().getGlobalBounds());});

  return it != fire.end();
}



bool Collision_handler::fire_hit_bomb(std::shared_ptr<Bomb>& bomb, 
				      std::vector<std::shared_ptr<Fire>>& fire){

  int bomb_tile = bomb->get_tile();
  std::vector<std::shared_ptr<Fire>>::iterator it;
  it = std::find_if(fire.begin(), fire.end(), 
		    [bomb_tile](std::shared_ptr<Fire> fire){return fire->get_tile() == bomb_tile;});

  return it != fire.end();
}



std::vector<int> Collision_handler::fire_hit_breakable(std::vector<std::shared_ptr<Fire>>& fire){
  std::vector<int> breakable_tiles;
  
  for(const auto& flame : fire){
    if((*m_tiles)[flame->get_tile()]->collision_effect == collision_effect_t::BREAKABLE)
      breakable_tiles.push_back(flame->get_tile());
  }

  return breakable_tiles;
}



bool Collision_handler::is_bomb_on_tile(int tile){
  std::vector<std::shared_ptr<Bomb>>::iterator it;
  it = std::find_if(m_bombs->begin(), m_bombs->end(), 
		    [tile](std::shared_ptr<Bomb> bomb){return bomb->get_tile()==tile;});
  
  return it != m_bombs->end();
}
