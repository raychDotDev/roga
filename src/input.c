#include "input.h"
#include <SDL2/SDL_events.h>

void InputHandler_init(InputHandler *ctx) {
    ctx->prevMouse = 0;
    ctx->prevMousePos = (v2i){};
    ctx->currentMouse = 0;
    ctx->currentMousePos = (v2i){};
    ctx->mouseWheel = (v2i){};
}

void InputHandler_update(InputHandler *ctx, SDL_Event e) {
    ctx->mouseWheel = (v2i){0, 0};
    if (e.type == SDL_MOUSEWHEEL) {
        ctx->mouseWheel.x = e.wheel.x;
        ctx->mouseWheel.y = e.wheel.y;
    }
    const u8 *state = SDL_GetKeyboardState(NULL);
    memcpy(ctx->prevKeys, ctx->currentKeys, KEY_STATE_SIZE);
    memcpy(ctx->currentKeys, state, KEY_STATE_SIZE);
    ctx->prevMouse = ctx->currentMouse;
    ctx->prevMousePos = ctx->currentMousePos;
    ctx->currentMouse =
        SDL_GetMouseState(&ctx->currentMousePos.x, &ctx->currentMousePos.y);
}
