#include "level.h"
#include "globals.h"

void setLevel(int level)
{
    player.x = 24 * grid;
    player.y = 4 * grid;
    player.jump = 0;
    player.state = STOP;
}