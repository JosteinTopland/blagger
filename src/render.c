#include <string.h>
#include <stdlib.h>

#include "render.h"
#include "globals.h"

static void draw_level() {
    for (int i = 0; i < level_width * level_height; i++) {
        if (!level[i] || level[i] == 0x12) continue;
        int x = (i % level_width) * level_grid;
        int y = (i / level_width) * level_grid;
        int spriteIdx = level[i] - 1;
        SpriteCoord sc = sprite_coords[spriteIdx];
        if (sc.frames > 1) sc.x += sc.width * ((SDL_GetTicks() / sc.fps) % sc.frames);
        SDL_Rect src = {sc.x, sc.y, sc.width, sc.height};
        SDL_Rect dst = {x, y, sc.width, sc.height};
        SDL_RenderCopy(renderer, sprites, &src, &dst);
    }
}

static void draw_blagger() {
    int x = player.x;
    int y = player.y;
    SpriteCoord sc = sprite_coords[HERO - 1];
    if (player.state & WALK) sc.x += sc.width * (SDL_GetTicks() / sc.fps % sc.frames);
    SDL_Rect src = {sc.x, sc.y, sc.width, sc.height};
    SDL_Rect dst = {x - 1, y - sc.height, sc.width, sc.height};
    SDL_RendererFlip flip = player.state & LEFT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, sprites, &src, &dst, 0, 0, flip);
}

static void draw_text(const char * text, int x, int y) {
    for (unsigned i = 0; i < strlen(text); i++) {
        if (text[i] == ' ') continue;
        int xx = (x + i) * level_grid;
        int yy = y * level_grid;
        SDL_Rect src = {(text[i] - 65) * 8 + 8, 63, 8, 8};
        SDL_Rect dst = {xx, yy, src.w, src.h};
        SDL_RenderCopy(renderer, sprites, &src, &dst);
    }
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_level();
    draw_blagger();
    draw_text("THE BANK", 12, 19);

    SDL_RenderPresent(renderer);
}

void retro_loader()
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
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
    Uint32 *pixels = malloc(window_width * window_height * sizeof(Uint32));
    for (int frames = 0; frames < 100; frames++) {
        if (frames < 80) {
            int length = 0;
            for (int i = 0; i < window_width * window_height; i++) {
                if (length == 0) {
                    colorIdx = (colorIdx + 1) % numColors;
                    length = rand() % (frames < 50 ? 1000 : 30000) + 1000;
                }
                length--;
                pixels[i] = colors[colorIdx];
            }
            SDL_UpdateTexture(texture, NULL, pixels, window_width * sizeof(Uint32));
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        } else {
            Uint32 color = colors[colorIdx];
            Uint8 r = (color & 0xff0000) >> 16;
            Uint8 g = (color & 0x00ff00) >> 8;
            Uint8 b = (color & 0x0000ff);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderClear(renderer);
        }

        SDL_Rect rect = {25, 30, window_width - 50, window_height - 60};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        draw_text("LOADING", 3, 5);

        // OSX fix
        SDL_Event event;
        SDL_PollEvent(&event);

        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
    free(pixels);
    SDL_DestroyTexture(texture);
}
