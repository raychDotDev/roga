#include "game.h"
#include "config.h"
#include "frameTimer.h"
#include "input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

Config *CONFIG;

InputHandler inputHandler = {};
FrameTimer frameTimer = {};

Game *Game_new() {
    Config_load();
    Game *game = (Game *)malloc(sizeof(Game));
    game->texture = NULL;
    game->screen = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
        return NULL;
    } else
        SDL_Log("Initialized all systems successfully\n");

    game->window = SDL_CreateWindow(
        CONFIG->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        CONFIG->windowSize.x, CONFIG->windowSize.y, SDL_WINDOW_RESIZABLE);
    if (game->window == NULL) {
        SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return NULL;
    } else
        SDL_Log("Initialized window successfully\n");

    SDL_RendererFlags flags = 0;
    // flags |= SDL_RENDERER_SOFTWARE;
    flags |= SDL_RENDERER_ACCELERATED;
    flags |= SDL_RENDERER_TARGETTEXTURE;

    game->renderer = SDL_CreateRenderer(game->window, -1, flags);
    if (game->renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return NULL;
    } else {
        SDL_Log("Renderer initialized successfully\n");
    }

    Game_setCanvasSize(game, CONFIG->canvasSize);
    game->running = b_true;

    InputHandler_init(&inputHandler);
    FrameTimer_init(&frameTimer);
    Game_setTargetFPS(CONFIG->targetFPS);
    return game;
}

void Game_destroy(Game *ctx) {
    Game_setScreen(ctx, NULL);
    SDL_Log("Unloaded screen\n");
    SDL_DestroyTexture(ctx->texture);
    SDL_Log("Unloaded texture\n");
    SDL_DestroyRenderer(ctx->renderer);
    SDL_Log("Unloaded renderer\n");
    SDL_DestroyWindow(ctx->window);
    SDL_Log("Unloaded window\n");
    free(ctx);
    SDL_Log("Unloaded game context\n");
    SDL_Quit();
    SDL_Log("Window closed successfully\n");
    Config_save();
}

void Game_stop(Game *ctx) {
    SDL_Log("Stopping game context...\n");
    ctx->running = b_false;
}

void Game_setCanvasSize(Game *ctx, v2i size) {
    if (ctx->texture != NULL)
        SDL_DestroyTexture(ctx->texture);
    ctx->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_ARGB32,
                                     SDL_TEXTUREACCESS_TARGET, size.x, size.y);
    CONFIG->canvasSize = size;
}

void Game_pollEvent(Game *ctx) {
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type) {
    case SDL_QUIT: {
        Game_stop(ctx);
    } break;

    case SDL_WINDOWEVENT: {
        // aparentlly, maximized event
        // comes AFTER changing size event.
        // because of that, we just skip one frame
        // so config.windowSize will not change
        // after window maximizing
        static bool_t pending_maximize = b_false;
        if (e.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
            CONFIG->maximized = b_true;
            pending_maximize = b_false;
        } else if (e.window.event == SDL_WINDOWEVENT_RESTORED) {
            CONFIG->maximized = b_false;
        } else if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            if (!CONFIG->maximized && !pending_maximize) {
                v2i resized = {0};
                SDL_GetWindowSize(ctx->window, &resized.x, &resized.y);
                CONFIG->windowSize = resized;
            }
        } else if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            pending_maximize = b_true;
        } else {
            pending_maximize = b_false;
        }
    } break;
    }
    InputHandler_update(&inputHandler, e);
    if (ctx->screen != NULL) {
        ctx->screen->update(ctx);
    }
}

void Game_render(Game *ctx) {
    SDL_SetRenderTarget(ctx->renderer, ctx->texture);
    SDL_SetRenderDrawColor(ctx->renderer, 100, 100, 100, 255);
    SDL_RenderClear(ctx->renderer);
    {
        if (ctx->screen != NULL) {
            ctx->screen->render(ctx);
        }
    }
    SDL_SetRenderTarget(ctx->renderer, NULL);
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);
    v2i windowSize = {};
    SDL_GetWindowSize(ctx->window, &windowSize.x, &windowSize.y);
    v2i canvasSize = CONFIG->canvasSize;
    f32 s = fminf((f32)windowSize.x / (f32)canvasSize.x,
                  (f32)windowSize.y / (f32)canvasSize.y);

    i32rect dest = {.pos = {windowSize.x / 2 - (i32)(canvasSize.x * s) / 2,
                            windowSize.y / 2 - (i32)(canvasSize.y * s) / 2},
                    .size = {(i32)(canvasSize.x * s), (i32)(canvasSize.y * s)}};

    SDL_Rect d = {dest.pos.x, dest.pos.y, dest.size.x, dest.size.y};
    SDL_RenderCopy(ctx->renderer, ctx->texture, NULL, &d);

    SDL_RenderPresent(ctx->renderer);
}

void Game_run(Game *ctx) {
    if (CONFIG->maximized) {
        SDL_MaximizeWindow(ctx->window);
    }
    SDL_Log("Started game context\n");
    while (ctx->running) {
        FrameTimer_preFrame(&frameTimer);
        Game_pollEvent(ctx);
        Game_render(ctx);
        FrameTimer_delay(&frameTimer);
        FrameTimer_postFrame(&frameTimer);
    }
    Game_destroy(ctx);
}

bool_t Game_keyPressed(SDL_Scancode code) {
    return (inputHandler.currentKeys[code] && !inputHandler.prevKeys[code]);
}

bool_t Game_keyReleased(SDL_Scancode code) {
    return (!inputHandler.currentKeys[code] && inputHandler.prevKeys[code]);
}

bool_t Game_keyDown(SDL_Scancode code) {
    return (inputHandler.currentKeys[code]);
}

bool_t Game_keyUp(SDL_Scancode code) {
    return (!inputHandler.currentKeys[code]);
}

v2i Game_mousePos() { return inputHandler.currentMousePos; }
v2i Game_mouseDelta() {
    return (v2i){inputHandler.prevMousePos.x - inputHandler.currentMousePos.x,
                 inputHandler.prevMousePos.y - inputHandler.currentMousePos.y};
}

v2i Game_mouseWheel() { return inputHandler.mouseWheel; }

bool_t Game_mousePressed(i32 mouseButton) {
    return (inputHandler.currentMouse & SDL_BUTTON(mouseButton)) &&
           !(inputHandler.prevMouse & SDL_BUTTON(mouseButton));
}

bool_t Game_mouseReleased(i32 mouseButton) {
    return !(inputHandler.currentMouse & SDL_BUTTON(mouseButton)) &&
           (inputHandler.prevMouse & SDL_BUTTON(mouseButton));
}

bool_t Game_mouseDown(i32 mouseButton) {
    return (inputHandler.currentMouse & SDL_BUTTON(mouseButton));
}

bool_t Game_mouseUp(i32 mouseButton) {
    return !(inputHandler.currentMouse & SDL_BUTTON(mouseButton));
}

void Game_setScreen(Game *ctx, Screen *value) {
    SDL_Log("Changing context screen...\n");
    if (ctx->screen != NULL) {
        SDL_Log("Screen is not NULL, Unloading previous value...\n");
        if (ctx->screen->unload != NULL) {
            ctx->screen->unload(ctx);
        }
        ctx->screen = NULL;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Setting new value...\n");
    ctx->screen = value;
    if (ctx->screen != NULL) {
        if (ctx->screen->load != NULL) {
            SDL_Log("Loading screen data...\n");
            ctx->screen->load(ctx);
        }
    }
    SDL_Log("Screen changed successfully\n");
}

i32 Game_getFPS() {
    i32 res = 0;
    for (i32 i = 0; i < FPS_BUFFER_SIZE; i++) {
        res += frameTimer.fps[i];
    }
    res /= FPS_BUFFER_SIZE;
    return res;
}

f32 Game_getTime() { return frameTimer.timerNow; }

f32 Game_getFrameTime() { return frameTimer.frameTime; }

void Game_setTargetFPS(u32 val) { CONFIG->targetFPS = val; }
