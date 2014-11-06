#include "game.h"
#include <fstream>
#include <iostream>
#include <functional>

Game::Game():
  collision_handler(new Collision_handler(&players, &bombs, &bonuses, &tiles)),
  input_handler(new Input_handler(players)) {}

bool Game::read_tiles(){
  Tile::init();

  std::fstream infile;
  infile.open("tilemap");
  
  int type;  
  int x = 0;
  int y = 0;
  const int h = 32;
  const int w = 32;
  
  while(infile >> type){
    collision_effect_t coll_eff = collision_effect_t::HARD;
    if(type == 2)
      coll_eff = collision_effect_t::TRANSPARENT;
    
    if(type == 1)
      coll_eff = collision_effect_t::BREAKABLE;

    tiles.emplace_back(std::make_shared<Tile>(x, y, w, h, type, coll_eff));
      
    x = (x + TILE_WIDTH) % WINDOW_WIDTH;
    if(x == 0)
      y = (y + TILE_HEIGHT) % WINDOW_HEIGHT;          
  }
  
  infile.close();
  return true;
}


bool Game::create_players(){
  players.emplace_back(std::make_shared<Player>("player1", 32, 32));
  players.emplace_back(std::make_shared<Player>("player2", 928, 608));
  return true;
}


bool Game::init(){
  if(!read_tiles())
    return false;
  
  if(!create_players())
    return false;
  
  input_handler->map_controlls(players);
  Bomb::init();
  Fire::init();
  return true;
}

void render_tiles(sf::RenderWindow& window, 
		  const std::vector<std::shared_ptr<Tile>>& tiles){  
  for(const auto& tile : tiles){	
    Tile::sprite.setTextureRect(sf::IntRect(tile->type * TILE_WIDTH, 0, 
						  tile->w, tile->h));
    Tile::sprite.setPosition(tile->x, tile->y);
    window.draw(Tile::sprite);
  }
}


int x_pos_from_tile(int tile){
  return (tile * TILE_WIDTH) % WINDOW_WIDTH;
}


int y_pos_from_tile(int tile){
  return std::floor(tile / TILES_PER_ROW) * TILE_HEIGHT;
}

void Game::place_fire(int range, int tile){
  std::vector<unsigned int> valid_fire_tiles = collision_handler->get_fire_pos(tile, range);

  for(const auto& fire_t : valid_fire_tiles){
    fire.emplace_back(std::make_shared<Fire>(x_pos_from_tile(fire_t),
					     y_pos_from_tile(fire_t),
					     TILE_HEIGHT,
					     TILE_WIDTH,
					     fire_t));
  }
}


void Game::drop_bomb(){
  for(const auto& player : players){
    if(player->is_dropping_bomb() && 
       player->get_ammo() &&
       !collision_handler->is_bomb_on_tile(player->get_tile())){
      
      player->drop_bomb();
      int range = player->get_bomb_range();
      int tile = player->get_tile();
      int x = x_pos_from_tile(tile);
      int y = y_pos_from_tile(tile);
      bombs.emplace_back(std::make_shared<Bomb>(range,x,y,tile, player));
    }
  }
}


void Game::delete_bombs(){
  int amount_to_erase = 0;
  for(auto& bomb : bombs){
    if(bomb->is_exploding()){      
      place_fire(bomb->get_range(), bomb->get_tile());
      amount_to_erase++;
    }
  }

  bombs.erase(bombs.begin(), bombs.begin() + amount_to_erase);
}


void Game::delete_fire(){
  int amount_to_erase = std::count_if(fire.begin(), fire.end(),
				  [](std::shared_ptr<Fire> fire){return fire->done_burning();});

  fire.erase(fire.begin(), fire.begin() + amount_to_erase);
}


void Game::do_actions(){
  drop_bomb();
  delete_bombs();
  delete_fire();
}


void Game::tile_to_bonus(int tile){
  //Transform current tile to transparent
  tiles[tile]->type = 2;
  tiles[tile]->collision_effect = collision_effect_t::TRANSPARENT;

  //Create bonus
  std::shared_ptr<Bonus> bonus = std::make_shared<Bonus>(tiles[tile]->x, tiles[tile]->y, tile);
  if(bonus->get_type() >= 0)
    bonuses.push_back(bonus);
}


void Game::check_fire_collision(){
  using namespace std::placeholders;

  for(auto& player : players){
    if(collision_handler->fire_hit_player(player, fire))
      player->decrement_life();
  }
 
  
  for(auto& bomb : bombs){
    if(!fire.empty(), collision_handler->fire_hit_bomb(bomb, fire))
      bomb->set_on_fire();  
  }
  

  std::vector<int> breakable_tiles = collision_handler->fire_hit_breakable(fire);
  std::for_each(breakable_tiles.begin(), breakable_tiles.end(), 
		std::bind(&Game::tile_to_bonus, this, _1));

}


void Game::check_bonus_collision(){
  std::vector<std::shared_ptr<Bonus>>::iterator it;
  for(const auto& player : players){
    for(it = bonuses.begin(); it != bonuses.end();){
      if(player->get_tile() == (*it)->get_tile()){
	(*it)->set_bonus(player);
	bonuses.erase(it);
      }
      else
	it++;
    }
  }
}


bool Game::read_input(){
  return input_handler->read_input(players);
}


void Game::set_pos(){
  for(auto& player : players)
    collision_handler->set_pos(player);
}

void Game::remove_dead_ppl(){
  std::vector<std::shared_ptr<Player>>::iterator it;  
  it = std::remove_if(players.begin(), players.end(), 
		      [](std::shared_ptr<Player> player){return player->get_lifes() <= 0;});

  players.resize(it - players.begin());
}

void present_winner(std::shared_ptr<Player> player){
//  std::cout << player->get_name() << std::endl;
  player->get_name();
}

void Game::check_for_winner(){
  if(players.size() == 1)
    present_winner(players[0]);
}

void Game::render_all(sf::RenderWindow& window){
  window.clear();

  render_tiles(window, tiles);
  render(window, bonuses);
  render(window, bombs);
  render(window, fire);
  render(window, players);
  
  window.display();
}

int Game::run(sf::RenderWindow& window){
  if(!init())
    return -1;

  while(read_input()){
    do_actions();
    check_fire_collision();
    check_bonus_collision();
    set_pos();
    remove_dead_ppl();
    check_for_winner();
    render_all(window);
  }
  return 0;
}
