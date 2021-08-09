#include "update.h"
#include "globals.h"

void update()
{
    int speed = 2;

    if (player.state & WALK) {
        
        player.x += player.state & LEFT ? -speed : player.state & RIGHT ? speed : 0;
    }
    if (player.state & JUMP) {
        player.y += player.jump <= 32 ? speed : -speed;
        player.jump -= speed;
        if (player.jump == 0) player.state ^= JUMP;
    } else if (!collision(&player)) {
        player.y += speed;
    }
}

SDL_bool collision(const struct Sprite *p) {
    int x = (p->x + 1) / grid;
    int y = p->y / grid;
    int idx = x + y * levelWidth;
    if (x < 0 || x >= levelWidth || y < 0 || y >= levelHeight) return SDL_TRUE;
    return level[idx] > 0;
}