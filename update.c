#include "update.h"
#include "globals.h"

void update()
{
  if (player.state & WALK) {
    player.x += player.state & LEFT ? -1 : player.state & RIGHT ? 1 : 0;
  }
  if (player.state & JUMP) {
    player.y += player.jump <= 16 ? 1 : -1;
    player.jump--;
    if (player.jump == 0) player.state ^= JUMP;
  } else if (!collision(&player)) {
    player.y++;
  }
}

SDL_bool collision(const struct Sprite *p) {
  int x = (p->x + 1) / grid;
  int y = p->y / grid;
  int idx = x + y * levelWidth;
  if (x < 0 || x >= levelWidth || y < 0 || y >= levelHeight) return SDL_TRUE;
  return level[idx] > 0;
}