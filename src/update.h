#ifndef UPDATE_H
#define UPDATE_H

#include <SDL.h>
#include "types.h"

void update();
SDL_bool collision(const struct Sprite *sprite, int x, int y);

#endif