#include "level.h"
#include "globals.h"

void setLevel(int level)
{
    player.x = 24 * grid;
    player.y = 3 * grid;
    player.x_velocity = 0;
    player.y_velocity = 0;
    player.state = LEFT;

    // Mix_PlayMusic(music, -1);
}
