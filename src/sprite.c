#include "sprite.h"
#include <raylib.h>
#include <stddef.h>

float Sprite_getFrameTime(Sprite *this) {
    return (1.f / (float)this->framesPerSecond);
}

void Sprite_play(Sprite *this) { this->playing = 1; }
void Sprite_stop(Sprite *this) { this->playing = 0; }

void Sprite_fromTexture(Texture atlas, int cols, int rows, int fps, Color tint,
                        Sprite *out) {
    out->atlas = atlas;
    out->playing = 0;
    out->end = 0;
    out->currentFrame = 0;
    out->cols = cols;
    out->rows = rows;
    out->framesPerSecond = fps;
    out->flipX = 0;
    out->flipY = 0;
    out->tint = tint;
}
void Sprite_update(Sprite *this) {
    float time = GetTime();
    if (this->timer == 0.0f) {
        this->timer = time;
    }
    if (this->playing) {
        if (time - this->timer >= Sprite_getFrameTime(this)) {
            this->currentFrame++;
            this->timer = time;
        }
    }
}

void Sprite_drawSeq(Sprite *this, Rectangle dest, float rotation,
                    SpriteFrame seq[], int seqc) {
    if (this->currentFrame >= seqc) {
        this->end = 1;
    }
    DrawTexturePro(this->atlas,
                   Sprite_getFrameRecBySeq(this, seq[this->currentFrame]), dest,
                   (Vector2){0.f, 0.f}, rotation, this->tint);
}

Rectangle Sprite_getFrameRec(Sprite *this) {
    Rectangle rect = {};
    int frameWidth = this->atlas.width / (this->cols == 0 ? 1 : this->cols);
    int frameHeight = this->atlas.height / (this->rows == 0 ? 1 : this->rows);
    rect.x = 0;
    rect.y = 0;
    rect.width = frameWidth;
    rect.height = frameHeight;
    return rect;
}

Rectangle Sprite_getFrameRecXY(Sprite *this, SpriteFrame frame) {
    Rectangle rect = Sprite_getFrameRec(this);
    rect.x = frame.col * rect.width;
    rect.x = frame.row * rect.width;
    return rect;
}

Rectangle Sprite_getCurrentFrameRec(Sprite *this) {
    return Sprite_getFrameRecXY(
        this, (SpriteFrame){this->currentCol, this->currentRow});
}

Rectangle Sprite_getFrameRecBySeq(Sprite *this, SpriteFrame pos) {
    Rectangle rect = {};
    int frameWidth = this->atlas.width / (this->cols == 0 ? 1 : this->cols);
    int frameHeight = this->atlas.height / (this->rows == 0 ? 1 : this->rows);
    rect.x = frameWidth * pos.col;
    rect.y = frameHeight * pos.row;
    rect.width = frameWidth;
    rect.height = frameHeight;
    printf("%f\n", rect.width);
    printf("%f\n", rect.height);
    return rect;
}
