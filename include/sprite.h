#pragma once

#include <raylib.h>

typedef struct _spriteFrame {
    int col;
    int row;
} SpriteFrame;

static const char *SPRITE_TEST_KEY = "man_white";
static SpriteFrame SPRITE_SEQ_TEST[7] = {{0, 0}, {1, 0}, {2, 0}, {3, 0},
                                         {4, 0}, {5, 0}, {6, 0}};
typedef struct {
    Texture atlas;
    float timer;
    int framesPerSecond;
    int currentCol;
    int currentRow;
    int cols;
    int rows;

    int flipX;
    int flipY;

    int currentFrame;

    int playing;
    int end;

    Color tint;
} Sprite;
void Sprite_play(Sprite *this);
void Sprite_stop(Sprite *this);
void Sprite_fromTexture(Texture atlas, int cols, int rows, int fps, Color tint,
                        Sprite *out);
float Sprite_getFrameTime(Sprite *this);
Rectangle Sprite_getFrameRec(Sprite *this);
void Sprite_update(Sprite *this);
void Sprite_drawSeq(Sprite *this, Rectangle dest, float rotation,
                    SpriteFrame seq[], int seqc);
Rectangle Sprite_getFrameRecBySeq(Sprite *this, SpriteFrame pos);
