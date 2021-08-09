#include <SDL.h>
#include <SDL_mixer.h>
#include "types.h"
#include "render.h"
#include "input.h"
#include "update.h"
#include "globals.h"
#include "level.h"

#define NO_STDIO_REDIRECT

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *sprites;
static Mix_Chunk *sounds[2];

void init()
{
    int width = windowWidth * windowScale;
    int height = windowHeight * windowScale;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_RenderSetScale(renderer, windowScale, windowScale);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);
    Mix_Volume(-1, 50);

    // load graphics
    SDL_Surface *surface = SDL_LoadBMP("assets/sprites.bmp");
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
    sprites = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // load sounds
    sounds[SND_WALK] = Mix_LoadWAV("assets/walk.wav");
    sounds[SND_JUMP] = Mix_LoadWAV("assets/jump.wav");
}

void quit()
{
    Mix_FreeChunk(sounds[0]);
    Mix_FreeChunk(sounds[1]);
    Mix_CloseAudio();
    SDL_DestroyTexture(sprites);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    init();
    retroLoader(renderer, sprites);
    setLevel(0);

    int run = 1;
    while (run) {
        int ticks = SDL_GetTicks();

        input(sounds, &run);
        update();
        render(renderer, sprites);

        int fps = 30;
        SDL_Delay(ticks + 1000 / fps - SDL_GetTicks());
    }

    quit();
}
