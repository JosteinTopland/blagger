#include <SDL2/SDL.h>
#include "types.h"
#include "render.h"
#include "input.h"
#include "update.h"
#include "globals.h"
#include "level.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *sprites;

void init()
{
    int width = windowWidth * windowScale;
    int height = windowHeight * windowScale;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_RenderSetScale(renderer, (float)windowScale, (float)windowScale);

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
}

void quit()
{
    Mix_FreeMusic(music);
    Mix_FreeChunk(sounds[0]);
    Mix_FreeChunk(sounds[1]);
    Mix_CloseAudio();
    SDL_DestroyTexture(sprites);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void blagger() {
    init();
    // retroLoader(renderer, sprites);
    setLevel(0);

    int run = 1;
    while (run) {
        // SDL_Log("hei\n");
        int ticks = SDL_GetTicks();

        input(&run);
        update();
        render(renderer, sprites);

        // wait
        int fps = 30;
        int delay = 1000 / fps - (SDL_GetTicks() - ticks);
        if (delay > 0) SDL_Delay(delay);
    }

    quit();
}

int main(int argc, char *argv[]) {
    blagger();
}
