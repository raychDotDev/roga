#include "data/screenMain.h"
#include "game.h"
#include "graphics.h"
#include "screen.h"
#include "typedef.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_video.h>
#include <omp.h>
#include <stdio.h>

void sm_load(Game *ctx);
void sm_unload(Game *ctx);
void sm_update(Game *ctx);
void sm_render(Game *ctx);

void ScreenMain_get(Screen *out) {
    Screen res = {};
    res.load = sm_load;
    res.unload = sm_unload;
    res.update = sm_update;
    res.render = sm_render;
    *out = res;
}

void sm_load(Game *ctx) {
    Game_setTargetFPS(120);
    Game_setCanvasSize(ctx, (v2i){640, 320});
}
void sm_unload(Game *ctx) { Game_setTargetFPS(80); }
void sm_update(Game *ctx) {}
void sm_render(Game *ctx) {
    char title[32];
    sprintf(title, "FPS: %d %f", Game_getFPS(), Game_getFrameTime());
    SDL_SetWindowTitle(ctx->window, title);
    u32rect rect = {(v2u){0, 0}, (v2u){ctx->canvas->w, ctx->canvas->h}};
    Graphics_rect(ctx, rect, 0xFFBBaa);
}
