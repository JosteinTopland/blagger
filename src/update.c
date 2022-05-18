#include "update.h"
#include "globals.h"

#include <stdio.h>

static int ground_collision() {
    if (player.y % 8 > 0) return 0;
    int p1 = (player.x + 5) / level_grid + player.y / level_grid * level_width;
    int p2 = (player.x + 6) / level_grid + player.y / level_grid * level_width;
    return level[p1] || level[p2] ? level[p1] : 0;

    // int p1 = (rect->x + 0 + x) / level_grid + (rect->y + y) / level_grid * level_width;
    // int p2 = (rect->x + 12 + x) / level_grid + (rect->y + y) / level_grid * level_width;
    // return level[p1] || level[p2]; 
    //
    //int w = sprite_coords[HERO - 1].width;
    //int h = sprite_coords[HERO - 1].height;
    //int p1 = (sprite->x + x) / grid + (sprite->y + y) / grid * levelw;
    //int p2 = (sprite->x + x + w) / grid + (sprite->y + y) / grid * levelw;
    // int p3 = (sprite->x + x + (sprite->y + y + h) * levelw) / grid;
    // int p4 = (sprite->x + x + w + (sprite->y + y + h) * levelw) / grid;
    //return level[p1] || level[p2]; // || level[p3] || level[p4];
    
    //if (x < 0 || x >= levelWidth || y < 0 || y >= levelHeight) return SDL_TRUE;
    //int idx = x + y * levelWidth;
    //return level[idx] > 0;
}

void update()
{
    int gravity = 1;
    int ground = ground_collision();

    if (ground) {
        if (player.y_velocity != 0) Mix_PlayChannel(1, sounds[SND_GROUND], 0);
        player.y_velocity = 0;
    } else {
        player.y_velocity = MAX(player.y_velocity - gravity, -gravity);
        // player.state &= ~WALK;
        if (!Mix_Playing(1)) Mix_PlayChannel(1, sounds[SND_FALL], 0);
    }

    if (player.state & WALK) {
        if (player.state & LEFT) player.x_velocity = -1;
        if (player.state & RIGHT) player.x_velocity = 1;
        if (!Mix_Playing(0)) Mix_PlayChannel(0, sounds[SND_WALK], -1);
        if (!ground) Mix_HaltChannel(0);
    } else {
        player.x_velocity = ground == 4 ? -1 : ground == 9 ? 1 : 0;
        Mix_HaltChannel(0);
    }

    if (player.state & JUMP && ground) {
        player.y_velocity = 6;
        player.state &= ~JUMP;
        Mix_PlayChannel(1, sounds[SND_JUMP], 0);
    }

    player.x += player.x_velocity;
    player.y -= player.y_velocity;

    return;
    SDL_Log("player.state=%d%d%d%d\t%d",
        (player.state & JUMP) > 0,
        (player.state & LEFT) > 0,
        (player.state & RIGHT) > 0,
        (player.state & WALK) > 0,
        player.y_velocity);
}
