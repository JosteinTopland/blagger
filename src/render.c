#include <string.h>
#include <stdlib.h>

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
    sc.x += sc.width * (player.state & RIGHT ? x/2 % sc.frames : sc.frames - 1 - (x/2) % sc.frames);
    SDL_Rect src = {sc.x, sc.y, sc.width, sc.height};
    SDL_Rect dst = {x - 1, y - sc.height, sc.width, sc.height};
    SDL_RendererFlip flip = (player.state & RIGHT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, sprites, &src, &dst, 0, 0, flip);
    // debug
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &dst);

    drawText(renderer, sprites, "THE BANK", 12, 19);

    SDL_RenderPresent(renderer);
}

void drawText(SDL_Renderer *renderer, SDL_Texture *sprites, const char * text, int x, int y) {
    for (unsigned i = 0; i < strlen(text); i++) {
        if (text[i] == ' ') continue;
        int xx = (x + i) * grid;
        int yy = y * grid;
        SDL_Rect src = {(text[i] - 65) * 16 + 16, 126, 16, 16};
        SDL_Rect dst = {xx, yy, src.w, src.h};
        SDL_RenderCopy(renderer, sprites, &src, &dst);
    }
}

void retroLoader(SDL_Renderer *renderer, SDL_Texture *sprites)
{
    const int numColors = 16;
    Uint32 colors[] = {
        0x000000,
        0xFFFFFF,
        0x9F4E44,
        0x6ABFC6,
        0xA057A3,
        0x5CAB5E,
        0x50459B,
        0xC9D487,
        0xA1683C,
        0x6D5412,
        0xCB7E75,
        0x626262,
        0x898989,
        0x9AE29B,
        0x887ECB,
        0xADADAD
    };

    int colorIdx = SDL_GetTicks() % numColors;
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
    Uint32 *pixels = malloc(windowWidth * windowHeight * sizeof(Uint32));
    for (int frames = 0; frames < 100; frames++) {
        if (frames < 80) {
            int length = 0;
            for (int i = 0; i < windowWidth * windowHeight; i++) {
                if (length == 0) {
                    colorIdx = (colorIdx + 1) % numColors;
                    length = 5000 + rand() % (frames < 50 ? 10000 : 50000);
                }
                length--;
                pixels[i] = colors[colorIdx];
            }
            SDL_UpdateTexture(texture, NULL, pixels, windowWidth * sizeof(Uint32));
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        } else {
            Uint32 color = colors[colorIdx];
            Uint8 r = (color & 0xff0000) >> 16;
            Uint8 g = (color & 0x00ff00) >> 8;
            Uint8 b = (color & 0x0000ff);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderClear(renderer);
        }

        SDL_Rect rect = {50, 60, windowWidth - 100, windowHeight - 120};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        drawText(renderer, sprites, "LOADING", 3, 4);

        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
    free(pixels);
    SDL_DestroyTexture(texture);
}