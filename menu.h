#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>

class Menu{
  sf::Texture texture;
  sf::Sprite sprite;

public:
  Menu();
  ~Menu() = default;
  
  bool show_menu(sf::RenderWindow& window);
  
};
#endif
