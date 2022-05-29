#include "level.h"
#include "globals.h"

void set_level(int num)
{
    for (int i = 0; i < level_height; i++) {
        for (int j = 0; j < level_width; j++) {
            if (level[i * level_width + j] == 0x12) {
                player.x = j * level_grid;
                player.y = i * level_grid;
                player.x_velocity = 0;
                player.y_velocity = 0;
                player.state = LEFT;
                break;
            }
        }
    }
    // TODO enemies must be sprites
    // Mix_PlayMusic(music, -1);
}
