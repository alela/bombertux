#include "input_handler.h"
#include "converter.h"
#include <fstream>
#include <iostream>

Input_handler::Input_handler(std::vector<std::shared_ptr<Player>>& _players)
  :m_players(_players){}


void Input_handler::read_config(std::string file){
  std::fstream infile;
  file = "config/"+file+".cfg";

  infile.open(file);
  std::string command, keystr;
  while(infile >> command && infile >> keystr){
    cfg_to_key[command] = Converter::string_to_key[keystr];
  }
  infile.close();
}

void Input_handler::read_movement(std::map<sf::Keyboard::Key, int*>& move_controlls){
  for(auto& i : move_controlls){
    *(i.second) = sf::Keyboard::isKeyPressed(i.first);
  }
}


void Input_handler::read_actions(std::map<sf::Keyboard::Key, int*>& action_controlls){
  for(auto& i : action_controlls){
    if(sf::Keyboard::isKeyPressed(i.first)){
      *(i.second) = 1;
    }
  }
}
