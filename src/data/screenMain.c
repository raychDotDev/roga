#include "data/screenMain.h"
#include "config.h"
#include "game.h"
#include "screen.h"
#include "typedef.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
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

void sm_load(Game *ctx) {}
void sm_unload(Game *ctx) {}
void sm_update(Game *ctx) {
    char title[32];
    sprintf(title, "FPS: %d %f", Game_getFPS(), Game_getFrameTime());
    SDL_SetWindowTitle(ctx->window, title);
    if (Game_keyPressed(SDL_SCANCODE_SPACE)) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "harro\n");
    }
}
void sm_render(Game *ctx) {
    // for (u32 j = 0; j < CONFIG->canvasSize.x; j++) {
    //     u8 v = 255;
    //     SDL_SetRenderDrawColor(ctx->renderer, v, v, v, 255);
    //     SDL_RenderDrawLine(ctx->renderer, j, 0, j, CONFIG->canvasSize.y - 1);
    // }
}
