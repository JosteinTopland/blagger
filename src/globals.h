#ifndef DATA_H
#define DATA_H

#include "types.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *sprites;

extern const int window_width;
extern const int window_height;
extern const int window_scale;

extern const int level_width;
extern const int level_height;
extern const int level_grid;

extern int main_loop;
extern Mix_Music *music;
extern Mix_Chunk *sounds[4];

extern const SpriteCoord sprite_coords[];
extern const char level[];

#endif
