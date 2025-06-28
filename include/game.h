#pragma once

#include "screen.h"
#include "typedef.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *canvas;
    SDL_Texture *texture;
	Screen* screen;
    bool_t running;
} Game;

i32 Game_getFPS();
void Game_setTargetFPS(i32 value);
f32 Game_getFrameTime();
f32 Game_getTime();

Game *Game_new(const char *title, v2i size, v2i canvasSize);
void Game_destroy(Game *ctx);

void Game_setCanvasSize(Game *ctx, v2i size);
void Game_run(Game *ctx);

void Game_stop(Game *ctx);

bool_t Game_keyPressed(SDL_Scancode code);
bool_t Game_keyReleased(SDL_Scancode code);
bool_t Game_keyDown(SDL_Scancode code);
bool_t Game_keyUp(SDL_Scancode code);

static const i32 MOUSE_LEFT = 1;
static const i32 MOUSE_MIDDLE = 2;
static const i32 MOUSE_RIGHT = 3;

v2i Game_mousePos();
v2i Game_mouseDelta();
v2i Game_mouseWheel();
bool_t Game_mousePressed(i32 mouseButton);
bool_t Game_mouseReleased(i32 mouseButton);
bool_t Game_mouseDown(i32 mouseButton);
bool_t Game_mouseUp(i32 mouseButton);

void Game_setScreen(Game* ctx, Screen* value);

void Game_setPixel(Game*ctx, v2u pos, u32 col);
