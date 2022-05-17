#ifndef DATA_H
#define DATA_H

#include "types.h"

#include <SDL2/SDL_mixer.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

extern const int windowWidth;
extern const int windowHeight;
extern const int windowScale;

extern const int levelWidth;
extern const int levelHeight;
extern const int grid;

extern int main_loop;
extern Mix_Music *music;
extern Mix_Chunk *sounds[2];

extern const SpriteCoord sprite_coords[];
extern const char level[];

#endif
