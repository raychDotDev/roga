#include "graphics.h"

void Graphics_rect(Game *ctx, u32rect rect, u32 color) {
    u32 endx = rect.pos.x + rect.size.x;
    u32 endy = rect.pos.y + rect.size.y;
    u32 canvasW = ctx->canvas->w;
    u32 canvasH = ctx->canvas->h;
#pragma omp parallel for schedule(static, 4)
    for (u32 i = rect.pos.y; i < endy; i++) {
        if (i >= canvasH) {
            continue;
        }
        for (u32 j = rect.pos.x; j < endx; j++) {
            if (j >= canvasW) {
                continue;
            }
            Game_setPixel(ctx, (v2u){j, i}, color);
        }
    }
}

void Graphics_rectLines(Game *ctx, u32rect rect, u32 color) {
#pragma omp parallel for schedule(static, 4)
    for (int i = rect.pos.y; i <= rect.pos.y + rect.size.y; i++) {
        Game_setPixel(ctx, (v2u){rect.pos.x, i}, color);
        Game_setPixel(ctx, (v2u){rect.pos.x + rect.size.x-1, i}, color);
    }
#pragma omp parallel for schedule(static, 4)
    for (int j = rect.pos.x; j <= rect.pos.x + rect.size.x; j++) {
        Game_setPixel(ctx, (v2u){j, rect.pos.y}, color);
        Game_setPixel(ctx, (v2u){j, rect.pos.y + rect.size.y-1}, color);
    }
}
