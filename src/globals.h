#ifndef DATA_H
#define DATA_H

#include "types.h"

#include <SDL.h>
#include <SDL_mixer.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define level_grid 8

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *sprites;

extern const int window_width;
extern const int window_height;
extern const int window_scale;

extern int main_loop;
extern Mix_Music *music;
extern Mix_Chunk *sounds[4];

extern const SpriteCoord sprite_coords[];

extern Sprite *player;
extern Sprite level_sprites[];
extern const int num_sprites;

extern const int level_width;
extern const int level_height;
extern const char level_map[];

#endif
