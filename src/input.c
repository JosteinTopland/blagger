#include <SDL.h>
#include "input.h"
#include "types.h"
#include "globals.h"

void input(Mix_Chunk *sounds[], int *run)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        player.state = LEFT | WALK;
                        if (!Mix_Playing(0)) Mix_PlayChannel(0, sounds[SND_WALK], -1);
                        break;
                    case SDLK_RIGHT:
                        player.state = RIGHT | WALK;
                        if (!Mix_Playing(0)) Mix_PlayChannel(0, sounds[SND_WALK], -1);
                        break;
                    case SDLK_SPACE:
                        if (!(player.state & JUMP)) {
                            player.state |= JUMP;
                            player.jump = 64;
                            Mix_PlayChannel(0, sounds[SND_JUMP], 0);
                        }
                        break;
                    case SDLK_q:
                        *run = 0;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (player.state & LEFT) {
                            player.state ^= WALK;
                            Mix_HaltChannel(0);
                        }
                        break;
                    case SDLK_RIGHT:
                        if (player.state & RIGHT) {
                            player.state ^= WALK;
                            Mix_HaltChannel(0);
                        }
                        break;
                    case SDLK_SPACE:
                        break;
                }
                break;
        }
    }
}