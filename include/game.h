#pragma once

#include "typedef.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* canvas;
	SDL_Texture* texture;
	bool_t running;
} Game;

Game* Game_new(v2i size, v2i canvasSize);
void Game_destroy(Game* ctx);

void Game_run(Game* ctx);

void Game_stop(Game* ctx);
