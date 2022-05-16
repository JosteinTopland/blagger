#include <SDL2/SDL.h>
#include "input.h"
#include "types.h"
#include "globals.h"

void input(int *run)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        player.state &= ~RIGHT;
                        player.state |= LEFT | WALK;
                        break;
                    case SDLK_RIGHT:
                        player.state &= ~LEFT;
                        player.state |= RIGHT | WALK;
                        break;
                    case SDLK_LCTRL:
                        player.state |= JUMP;
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
                        }
                        break;
                    case SDLK_RIGHT:
                        if (player.state & RIGHT) {
                            player.state ^= WALK;
                        }
                        break;
                    case SDLK_SPACE:
                        break;
                }
                break;
        }
    }
}
