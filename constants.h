#ifndef CONSTANTS_H
#define CONSTANTS_H
const int WINDOW_WIDTH = 992;
const int WINDOW_HEIGHT = 672;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TILES_PER_ROW = WINDOW_WIDTH / TILE_WIDTH;
const int PLAYER_WIDTH = 30;
const int PLAYER_HEIGHT = 30;
enum collision_effect_t{TRANSPARENT, BREAKABLE, HARD};
#endif
