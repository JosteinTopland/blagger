#ifndef UPDATE_H
#define UPDATE_H

#include <SDL2/SDL.h>

void update();
SDL_bool tile_collision(const SDL_Rect *rect, int x, int y);

#endif
