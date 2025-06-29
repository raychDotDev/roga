#include "frameTimer.h"
#include "config.h"

void FrameTimer_init(FrameTimer *ctx) {
    ctx->frameTime = 0.f;
    ctx->timerNow = SDL_GetTicks();
    ctx->timerOld = SDL_GetTicks();
    ctx->fpsIndex = 0;
}
void FrameTimer_delay(FrameTimer *ctx) {
        i32 target = CONFIG->targetFPS;
        i32 delay = target == 0 ? 0 : (i32)((1.f / target) * 1000);
        if (delay > 0)
            SDL_Delay(delay);
}
void FrameTimer_preFrame(FrameTimer *ctx) { ctx->timerOld = ctx->timerNow; }
void FrameTimer_postFrame(FrameTimer *ctx) {
        ctx->timerNow = SDL_GetTicks();
        ctx->frameTime = (ctx->timerNow - ctx->timerOld) * 0.001f;
        ctx->fps[ctx->fpsIndex] = (i32)(1.f / ctx->frameTime);
        ctx->fpsIndex = (ctx->fpsIndex + 1) % FPS_BUFFER_SIZE;
}
