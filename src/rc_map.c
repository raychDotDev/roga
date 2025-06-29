#include "rc_map.h"
#include "typedef.h"

bool_t assertMapPos(Map *ctx, v2u pos) {
    if (pos.x >= ctx->size.x || pos.y >= ctx->size.y ||
        pos.x >= MAP_MAXSIZE_X || pos.y >= MAP_MAXSIZE_Y) {
        return b_false;
    }
    return b_true;
}

void Map_getWallAt(Map *ctx, v2u pos, Tile *out) {
    if (!assertMapPos(ctx, pos)) {
        out = NULL;
        return;
    }
    *out = ctx->wallMap[pos.y * ctx->size.x + pos.x];
}
void Map_getFloorAt(Map *ctx, v2u pos, Tile *out) {
    if (!assertMapPos(ctx, pos)) {
        out = NULL;
        return;
    }
    *out = ctx->floorMap[pos.y * ctx->size.x + pos.x];
}
void Map_getCeilingAt(Map *ctx, v2u pos, Tile *out) {
    if (!assertMapPos(ctx, pos)) {
        out = NULL;
        return;
    }
    *out = ctx->ceilMap[pos.y * ctx->size.x + pos.x];
}

void Map_setWallAt(Map *ctx, v2u pos, Tile val) {
    if (!assertMapPos(ctx, pos)) {
        return;
    }
	ctx->wallMap[pos.y * ctx->size.x + pos.x] = val;

}
void Map_setFloorAt(Map *ctx, v2u pos, Tile val) {
    if (!assertMapPos(ctx, pos)) {
        return;
    }
	ctx->floorMap[pos.y * ctx->size.x + pos.x] = val;
}
void Map_setCeilingAt(Map *ctx, v2u pos, Tile val) {
    if (!assertMapPos(ctx, pos)) {
        return;
    }
	ctx->ceilMap[pos.y * ctx->size.x + pos.x] = val;
}
