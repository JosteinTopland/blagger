#include "render.h"
#include "globals.h"

void render(SDL_Renderer *renderer, SDL_Texture *sprites)
{
  int ticks = SDL_GetTicks();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // draw level
  int w = 31;
  int h = 19;
  for (int i = 0; i < w * h; i++) {
    if (!level[i]) continue;
    int x = (i % w) * grid;
    int y = (i / w) * grid;
    int spriteIdx = level[i] - 1;
    SpriteCoord sc = sprite_coords[spriteIdx];
    if (sc.animate) {
      sc.x += sc.width * ((ticks / sc.fps) % sc.frames);
    }
    SDL_Rect src = {sc.x, sc.y, sc.width, sc.height};
    SDL_Rect dst = {x, y, sc.width, sc.height};
    SDL_RenderCopy(renderer, sprites, &src, &dst);
  }

  // draw hero
  int x = player.x;
  int y = player.y;
  SpriteCoord sc = sprite_coords[HERO - 1];
  sc.x += sc.width * (player.state & RIGHT ? x % sc.frames : sc.frames - 1 - x % sc.frames);
  SDL_Rect src = {sc.x, sc.y, sc.width, sc.height};
  SDL_Rect dst = {x - 1, y - sc.height, sc.width, sc.height};
  SDL_RendererFlip flip = (player.state & RIGHT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  SDL_RenderCopyEx(renderer, sprites, &src, &dst, 0, 0, flip);
  if (0) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &dst);
  }

  drawText(renderer, sprites, "THE BANK", 12, 19);

  SDL_RenderPresent(renderer);
}

void drawText(SDL_Renderer *renderer, SDL_Texture *sprites, const char * text, int x, int y) {
  for (int i = 0; i < strlen(text); i++) {
    if (text[i] == ' ') continue;
    int xx = (x + i) * grid;
    int yy = y * grid;
    SDL_Rect src = {(text[i] - 65) * 8 + 8, 63, 8, 8};
    SDL_Rect dst = {xx, yy, src.w, src.h};
    SDL_RenderCopy(renderer, sprites, &src, &dst);
  }
}

void retroLoader(SDL_Renderer *renderer, SDL_Texture *sprites)
{
  const int numColors = 16;
  SDL_Color colors[] = {
    {0x00, 0x00, 0x00},
    {0xFF, 0xFF, 0xFF},
    {0x9F, 0x4E, 0x44},
    {0x6A, 0xBF, 0xC6},
    {0xA0, 0x57, 0xA3},
    {0x5C, 0xAB, 0x5E},
    {0x50, 0x45, 0x9B},
    {0xC9, 0xD4, 0x87},
    {0xA1, 0x68, 0x3C},
    {0x6D, 0x54, 0x12},
    {0xCB, 0x7E, 0x75},
    {0x62, 0x62, 0x62},
    {0x89, 0x89, 0x89},
    {0x9A, 0xE2, 0x9B},
    {0x88, 0x7E, 0xCB},
    {0xAD, 0xAD, 0xAD}
  };
  int w = 320;
  int h = 200;

  int colorIdx = SDL_GetTicks() % numColors;
  for (int frames = 0; frames < 80; frames++) {
    if (frames < 40) {
      for (int pos = 0; pos < w * h;) {
        int numPoints = 1000 + rand() % 3000;
        SDL_Point points[numPoints];
        for (int j = 0; j < numPoints; j++) {
          points[j].x = pos % w;
          points[j].y = pos / w;
          pos++;
        }
        SDL_Color color = colors[colorIdx];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawPoints(renderer, points, numPoints);
        colorIdx = (colorIdx + 1) % numColors;
      }
    } else {
      SDL_Color color = colors[colorIdx];
      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
      SDL_RenderClear(renderer);
    }

    SDL_Rect rect = {25, 30, w - 50, h - 60};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    drawText(renderer, sprites, "LOADING", 3, 4);

    SDL_RenderPresent(renderer);
    SDL_Delay(20);
  }
}