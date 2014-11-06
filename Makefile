
all:  fire bomb player converter input collision tile bonus game menu main
	g++ -std=c++11 fire.o bomb.o player.o input_handler.o converter.h tile.o bonus.o collision_handler.o game.o menu.o main.o -o Bombertux -lsfml-graphics -lsfml-window -lsfml-system


player: player_h player.cpp
	g++ -c -std=c++11 player.cpp

player_h: player.h
	g++ -c -std=c++11 player.h

converter: converter.h
	g++ -c -std=c++11 converter.h

input: input_h input_handler.cpp
	g++ -c -std=c++11 input_handler.cpp

input_h: input_handler.h
	g++ -c -std=c++11 input_handler.h

collision: coll.h collision_handler.cpp
	g++ -c -std=c++11 collision_handler.cpp

coll.h: collision_handler.h
	g++ -c -std=c++11 collision_handler.h

tile:	tile_h tile.cpp 
	g++ -c -std=c++11 tile.cpp

tile_h: tile.h
	g++ -c -std=c++11 tile.h

bomb: bomb_h bomb.cpp
	g++ -c -std=c++11 bomb.cpp

bomb_h: bomb.h 
	g++ -c -std=c++11 bomb.h

fire: fire_h fire.cpp
	g++ -c -std=c++11 fire.cpp

fire_h:
	g++ -c -std=c++11 fire.h

bonus: bonus_h bonus.cpp
	g++ -c -std=c++11 bonus.cpp

bonus_h: bonus.h
	g++ -c -std=c++11 bonus.h

game: game_h game.cpp
	g++ -c -std=c++11 game.cpp

game_h: game.h	
	g++ -c -std=c++11 game.h

menu: menu_h menu.cpp
	g++ -c -std=c++11 menu.cpp

menu_h: menu.h
	g++ -c -std=c++11 menu.h

main: main.cpp
	g++ -c -std=c++11 main.cpp



