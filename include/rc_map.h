#pragma once

#include "rc_skybox.h"
#define MAP_MAXSIZE_X 512
#define MAP_MAXSIZE_Y 512

#include "rc_tile.h"
typedef struct {
    Tile wallMap[MAP_MAXSIZE_X * MAP_MAXSIZE_Y];
    Tile floorMap[MAP_MAXSIZE_X * MAP_MAXSIZE_Y];
    Tile ceilMap[MAP_MAXSIZE_X * MAP_MAXSIZE_Y];
	SkyBox skyBox;
    v2u size;
} Map;

void Map_getWallAt(Map *ctx, v2u pos, Tile *out);
void Map_getFloorAt(Map *ctx, v2u pos, Tile *out);
void Map_getCeilingAt(Map *ctx, v2u pos, Tile *out);

void Map_setWallAt(Map *ctx, v2u pos, Tile val);
void Map_setFloorAt(Map *ctx, v2u pos, Tile val);
void Map_setCeilingAt(Map *ctx, v2u pos, Tile val);
