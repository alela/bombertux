#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "menu.h"

int main()
{
  

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bombertux!");
  window.setFramerateLimit(200);
  //Menu menu;

  //if(!menu.show_menu(window))
  // window.close();
  
  Game game;
  game.run(window);

  window.close();

  return 0;
}










/*#include <SFML/Graphics.hpp>
#include "player.h"
#include "collision_handler.h"
#include "tile.h"
#include <iostream>
#include <fstream>

void read_tiles(std::vector<Tile*>& tiles){
  std::fstream infile;
  infile.open("tilemap");
  
  int type;
  int x = 0;
  int y = 0;
  const int h = 32;
  const int w = 32;
  while(infile >> type){
    tiles.emplace_back(new Tile(x, y, w, h, type, 0));
    
    x = (x + 32) % 1024;
    if(x == 0)
      y = (y + 32) % 672;
          
  }
}

void draw_tiles(sf::RenderWindow& window, std::vector<Tile*>& tiles){
  
  sf::Texture texture;
  texture.loadFromFile("resources/tiletextures.png");
  sf::Sprite sprite(texture);
  for(const auto& tile : tiles){
    sprite.setTextureRect(sf::IntRect(tile->type * 32, 0, tile->w, tile->h));
    sprite.setPosition(tile->x, tile->y);
    window.draw(sprite);
  }
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML works!");

  std::vector<Tile*> tiles;   
  
  read_tiles(tiles);

  Player* player1 = new Player();
  Player* player2 = new Player();
  std::vector<Player*> players;
  players.push_back(player1);
  players.push_back(player2);

  Collision_handler* pos_handler = new Collision_handler(players);
  Bomb* b = player1->drop_bomb();
  Fire* f = nullptr;

  while (window.isOpen())
  {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      window.close();

    pos_handler->read_input();
	
	
//	b = player1->drop_bomb();
    pos_handler->set_pos();


    window.clear();

    draw_tiles(window, tiles);

    window.draw(player1->get_sprite());

    if(b != nullptr && b->is_exploding()){
      f = b->explode();
      delete b;
      b = nullptr;
    }

    if(b != nullptr)
      window.draw(b->get_sprite());
    if(f != nullptr)
      window.draw(f->get_sprite());

    window.display();
  }

  std::cerr << "SLUT På DET ROLIGA!" << std::endl;    

  for(auto & tile : tiles)
    delete tile;

  delete f;
  delete pos_handler;
  delete player2;
  delete player1;    

  return 0;
}

  

*/
  
