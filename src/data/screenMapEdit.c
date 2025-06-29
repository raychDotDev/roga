#include "data/screenMapEdit.h"
#include "game.h"
#include <SDL2/SDL_render.h>

void sme_load(Game *ctx);
void sme_unload(Game *ctx);
void sme_update(Game *ctx);
void sme_render(Game *ctx);

void ScreenMapEdit_get(Screen *out) {
    Screen res = {};
    res.load = sme_load;
    res.unload = sme_unload;
    res.render = sme_render;
    res.update = sme_update;
    *out = res;
}

void sme_load(Game *ctx) {}
void sme_unload(Game *ctx) {}
void sme_render(Game *ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);
    SDL_Rect r = {0, 0, 100, 100};
    SDL_RenderDrawRect(ctx->renderer, &r);
}
void sme_update(Game *ctx) {}
