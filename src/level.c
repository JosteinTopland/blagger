#include "level.h"
#include "globals.h"

void set_level(int level)
{
    player.x = 24 * level_grid;
    player.y = 4 * level_grid;
    player.x_velocity = 0;
    player.y_velocity = 0;
    player.state = LEFT;

    // Mix_PlayMusic(music, -1);
}
