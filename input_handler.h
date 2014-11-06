#ifndef INPUT_HANDER_H
#define INPUT_HANDER_H

#include "player.h"
#include <vector>
#include <map>

class Input_handler{

  std::vector<std::shared_ptr<Player>>& m_players;
  std::map<std::string, sf::Keyboard::Key> cfg_to_key;
  
  void read_config(std::string file);
  void read_movement(std::map<sf::Keyboard::Key, int*>& move_controlls);
  void read_actions(std::map<sf::Keyboard::Key, int*>& action_controlls);
  
public:
  Input_handler(std::vector<std::shared_ptr<Player>>&);
  ~Input_handler() = default;
  
  template<typename T> void map_controlls(T entities);
  template<typename T> bool read_input(T entities);
};



template<typename T> void Input_handler::map_controlls(T entities){
  for(auto& entity : entities){
    read_config(entity->name);
    entity->move_controlls[cfg_to_key["moving_up"]] = &(entity->moving_up);
    entity->move_controlls[cfg_to_key["moving_down"]] = &(entity->moving_down);
    entity->move_controlls[cfg_to_key["moving_left"]] = &(entity->moving_left);
    entity->move_controlls[cfg_to_key["moving_right"]] = &(entity->moving_right);
    entity->action_controlls[cfg_to_key["dropping_bomb"]] = &(entity->dropping_bomb);
  }
}


template<typename T> 
bool Input_handler::read_input(T entities){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    return false;
  
  for(auto& entity : entities){
    read_movement(entity->get_mv_ctrls());
    read_actions(entity->get_action_ctrls());      
  }
  return true;
}



#endif
