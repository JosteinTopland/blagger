#ifndef TYPES_H
#define TYPES_H

enum {
    SND_MOVE = 0,
    SND_JUMP = 1,
    SND_FALL = 2,
    SND_GROUND = 3
};

typedef enum {
    BRICK = 0x01,
    CAR = 0x11,
    HERO = 0x12
} Type;

typedef enum {
    MOVE = 1,
    RIGHT = 2,
    LEFT = 4,
    JUMP = 8
} PlayerState;

typedef struct {
    Type type;
    int x;
    int y;
    PlayerState state;
    int x_velocity;
    int y_velocity;
} Sprite;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int frames;
    int fps;
} SpriteCoord;

#endif
