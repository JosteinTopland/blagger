#include "level.h"
#include "globals.h"

void setLevel(int level)
{
    player.x = 24 * grid;
    player.y = 3 * grid;
    player.state = LEFT;
    player.jump = 0;

    // Mix_PlayMusic(music, -1);
}
