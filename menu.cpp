#include "menu.h"


Menu::Menu(){
  texture.loadFromFile("resources/menu.png");
  sprite.setTexture(texture);
}

bool Menu::show_menu(sf::RenderWindow& window){
  while(1){
    window.clear();
    window.draw(sprite);
    window.display();
  }
  
  return true;
}
