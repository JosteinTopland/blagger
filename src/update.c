#include "update.h"
#include "globals.h"

#include <stdio.h>

void update()
{
    int speed = 2;
    if (player.state & WALK && !collision(&player, 0, 0)) {
        player.x += player.state & LEFT ? -speed : player.state & RIGHT ? speed : 0;
    }
    return;
    /*if (player.state & JUMP) {
        player.y += player.jump <= 32 ? speed : -speed;
        player.jump -= speed;
        if (player.jump == 0) player.state ^= JUMP;
    } else if (false) {
        player.y += speed;
    }*/
}

SDL_bool collision(const struct Sprite *sprite, int x, int y) {
    int levelw = 31; // todo make globals

    int w = sprite_coords[HERO - 1].width;
    int h = sprite_coords[HERO - 1].height;
    int p1 = (sprite->x + x + (sprite->y + y) * levelw) / grid;
    int p2 = (sprite->x + x + w + (sprite->y + y) * levelw) / grid;
    int p3 = (sprite->x + x + (sprite->y + y + h) * levelw) / grid;
    int p4 = (sprite->x + x + w + (sprite->y + y + h) * levelw) / grid;
    return level[p1] || level[p2] || level[p3] || level[p4];
    
    //if (x < 0 || x >= levelWidth || y < 0 || y >= levelHeight) return SDL_TRUE;
    //int idx = x + y * levelWidth;
    //return level[idx] > 0;
}