#pragma once

#include "game.h"
#include "typedef.h"
#include <SDL2/SDL_pixels.h>

void Graphics_rect(Game *ctx, u32rect rect, u32 color);
void Graphics_rectLines(Game *ctx, u32rect rect, u32 color);
