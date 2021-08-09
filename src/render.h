#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "types.h"

void render(SDL_Renderer *renderer, SDL_Texture *sprites);
void drawText(SDL_Renderer *renderer, SDL_Texture *sprites, const char * text, int x, int y);
void retroLoader(SDL_Renderer *renderer, SDL_Texture *sprites);

#endif