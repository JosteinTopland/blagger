#ifndef TYPES_H
#define TYPES_H

enum {
    SND_WALK = 0,
    SND_JUMP = 1
};

enum {
    BRICK = 0x01,
    HERO = 0x12
};

typedef enum {
    WALK = 1,
    RIGHT = 2,
    LEFT = 4,
    JUMP = 8
} PlayerState;

struct Sprite {
    int x;
    int y;
    int jump;
    PlayerState state;
} player;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int frames;
    int fps;
    char animate;
} SpriteCoord;

#endif
