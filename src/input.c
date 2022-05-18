#include <SDL2/SDL.h>
#include "input.h"
#include "types.h"
#include "globals.h"

void input()
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
                    case SDLK_UP:
                        player.state |= JUMP;
                        break;
                    case SDLK_q:
                        main_loop = 0;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        if (player.state & LEFT || player.state & RIGHT) {
                            player.state &= ~WALK;
                        }
                        break;
                }
                break;
        }
    }
}
