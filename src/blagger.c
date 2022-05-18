#include "render.h"
#include "input.h"
#include "update.h"
#include "globals.h"
#include "level.h"

#include <SDL2/SDL.h>

void init()
{
    int width = window_width * window_scale;
    int height = window_height * window_scale;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_RenderSetScale(renderer, (float)window_scale, (float)window_scale);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);
    Mix_Volume(-1, 50);

    // load graphics
    SDL_Surface *surface = SDL_LoadBMP("assets/sprites.bmp");
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
    sprites = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // load audio
    music = Mix_LoadMUS("assets/CROWN.MOD");
    sounds[SND_WALK] = Mix_LoadWAV("assets/walk.wav");
    sounds[SND_JUMP] = Mix_LoadWAV("assets/jump.wav");
    sounds[SND_FALL] = Mix_LoadWAV("assets/fall.wav");
    sounds[SND_GROUND] = Mix_LoadWAV("assets/ground.wav");
    Mix_Volume(-1, 128);
}

void quit()
{
    Mix_FreeMusic(music);
    Mix_FreeChunk(sounds[0]);
    Mix_FreeChunk(sounds[1]);
    Mix_FreeChunk(sounds[2]);
    Mix_FreeChunk(sounds[3]);
    Mix_CloseAudio();
    SDL_DestroyTexture(sprites);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void blagger() {
    init();
    // retro_loader();
    set_level(0);

    while (main_loop) {
        int ticks = SDL_GetTicks();

        input();
        update();
        render();

        // wait
        int fps = 30;
        int delay = 1000 / fps - (SDL_GetTicks() - ticks);
        if (delay > 0) SDL_Delay(delay);
    }

    quit();
}

int main(int argc, char *argv[]) {
    blagger();
    return 0;
}
