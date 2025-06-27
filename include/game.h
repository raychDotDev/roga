#pragma once

#include "typedef.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *canvas;
    SDL_Texture *texture;
    bool_t running;
} Game;

Game *Game_new(const char *title, v2i size, v2i canvasSize);
void Game_destroy(Game *ctx);

void Game_changeCanvasSize(Game *ctx, v2i size);
void Game_run(Game *ctx);

void Game_stop(Game *ctx);

bool_t Game_keyPressed(SDL_Scancode code);
bool_t Game_keyReleased(SDL_Scancode code);
bool_t Game_keyDown(SDL_Scancode code);
bool_t Game_keyUp(SDL_Scancode code);
