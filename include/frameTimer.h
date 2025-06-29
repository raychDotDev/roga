#pragma once

#define FPS_BUFFER_SIZE 30

#include "typedef.h"
typedef struct {
    i32 timerOld;
    i32 timerNow;
    f32 frameTime;
    i32 fps[FPS_BUFFER_SIZE];
    i32 fpsIndex;
} FrameTimer;

void FrameTimer_init(FrameTimer* ctx);
void FrameTimer_delay(FrameTimer* ctx);
void FrameTimer_preFrame(FrameTimer* ctx);
void FrameTimer_postFrame(FrameTimer* ctx);
