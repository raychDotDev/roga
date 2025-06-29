#pragma once

#include "typedef.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#define RC_TILE_MAX_TEXTURE_KEY 64
typedef struct {
	u32 textureID;
	SDL_Color tint;
	bool_t transparent;
	// TODO: implement
	// void (*interact)();
} Tile;
