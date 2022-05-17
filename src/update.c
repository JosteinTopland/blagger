#include "update.h"
#include "globals.h"

#include <stdio.h>

void update()
{
    int gravity = 1;

    SDL_Rect rect = { player.x + (player.state & LEFT ? 0 : 12), player.y, 10, 10 };
    SDL_bool on_ground = tile_collision(&rect, 0, 0);

    if (on_ground) {
        if (!(player.state & WALK)) player.x_velocity = 0;
        player.y_velocity = 0;
    } else {
        player.y_velocity = MAX(player.y_velocity - gravity, -gravity);
        player.state &= ~WALK;
    }

    if (player.state & WALK) {
        if (player.state & LEFT) player.x_velocity = -1;
        if (player.state & RIGHT) player.x_velocity = 1;
        if (!Mix_Playing(0)) Mix_PlayChannel(0, sounds[SND_WALK], -1);
    } else {
        Mix_HaltChannel(0);
    }

    if (player.state & JUMP && on_ground) {
        player.y_velocity = 6;
        player.state &= ~JUMP;
        Mix_PlayChannel(1, sounds[SND_JUMP], 0);
    }

    player.x += windowScale * player.x_velocity;
    player.y -= windowScale * player.y_velocity;

    SDL_Log("player.state=%d%d%d%d\t%d",
        (player.state & JUMP) > 0,
        (player.state & LEFT) > 0,
        (player.state & RIGHT) > 0,
        (player.state & WALK) > 0,
        player.y_velocity);
}

SDL_bool tile_collision(const SDL_Rect *rect, int x, int y) {
    int p1 = (rect->x + 0 + x) / grid + (rect->y + y) / grid * levelWidth;
    int p2 = (rect->x + 12 + x) / grid + (rect->y + y) / grid * levelWidth;
    return level[p1] || level[p2];

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
