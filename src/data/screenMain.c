#include "data/screenMain.h"
#include "game.h"
#include "screen.h"

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
void sm_update(Game *ctx) {}
void sm_render(Game *ctx) {}
