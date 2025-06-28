#include "game.h"
#include "config.h"
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

#define KEY_STATE_SIZE 512

u8 prevKeys[KEY_STATE_SIZE];
u8 currentKeys[KEY_STATE_SIZE];
u32 prevMouse = 0;
v2i prevMousePos = {};
u32 currentMouse = 0;
v2i currentMousePos = {};
v2i mouseWheel = {};
i32 timerOld = 0;
i32 timerNow = 0;
f32 frameTime = 0;

#define fpsBufferSize 30

i32 fps[fpsBufferSize] = {};
i32 fpsIndex = 0;

Game *Game_new(const char *title, v2i size, v2i canvasSize) {
    Game *game = (Game *)malloc(sizeof(Game));
    game->canvas = NULL;
    game->texture = NULL;
    game->screen = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init Error: %s\n",
                     SDL_GetError());
        return NULL;
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Initialized all systems successfully\n");
    }

    game->window =
        SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         size.x, size.y, SDL_WINDOW_RESIZABLE);
    if (game->window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return NULL;
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Initialized window successfully\n");
    }

    game->renderer =
        SDL_CreateRenderer(game->window, -1, SDL_RENDERER_SOFTWARE);
    if (game->renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return NULL;
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Renderer initialized successfully\n");
    }

    Game_setCanvasSize(game, CONFIG.canvasSize);
    game->running = b_true;

    const u8 *state = SDL_GetKeyboardState(NULL);
    memcpy(currentKeys, state, KEY_STATE_SIZE);
    memcpy(prevKeys, currentKeys, KEY_STATE_SIZE);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                "Fetched initial keyboard state\n");
    u32 mouse = SDL_GetMouseState(&currentMousePos.x, &currentMousePos.y);
    prevMouse = mouse;
    prevMousePos = currentMousePos;
    currentMouse = mouse;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fetched initial mouse state\n");
    timerNow = SDL_GetTicks64();
    timerOld = timerNow;
    return game;
}

void Game_destroy(Game *ctx) {
    Game_setScreen(ctx, NULL);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Unloaded screen\n");
    SDL_FreeSurface(ctx->canvas);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Unloaded canvas\n");
    SDL_DestroyTexture(ctx->texture);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Unloaded texture\n");
    SDL_DestroyRenderer(ctx->renderer);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Unloaded renderer\n");
    SDL_DestroyWindow(ctx->window);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Unloaded window\n");
    free(ctx);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Unloaded game context\n");
    SDL_Quit();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Window closed successfully\n");
}

void Game_stop(Game *ctx) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Stopping game context...\n");
    ctx->running = b_false;
}

void Game_setCanvasSize(Game *ctx, v2i size) {
    if (ctx->canvas != NULL)
        SDL_FreeSurface(ctx->canvas);
    if (ctx->texture != NULL)
        SDL_DestroyTexture(ctx->texture);
    ctx->canvas = SDL_CreateRGBSurfaceWithFormat(0, size.x, size.y, 32,
                                                 SDL_PIXELFORMAT_RGB888);
    ctx->texture = SDL_CreateTextureFromSurface(ctx->renderer, ctx->canvas);
    CONFIG.canvasSize = size;
}

void Game_pollEvent(Game *ctx) {
    SDL_Event e;
    SDL_PollEvent(&e);
    mouseWheel = (v2i){0, 0};
    switch (e.type) {
    case SDL_QUIT: {
        Game_stop(ctx);
    } break;

    case SDL_WINDOWEVENT: {
        static bool_t pending_maximize = b_false;

        if (e.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
            CONFIG.maximized = b_true;
            pending_maximize = b_false;
        } else if (e.window.event == SDL_WINDOWEVENT_RESTORED) {
            CONFIG.maximized = b_false;
        } else if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            if (!CONFIG.maximized && !pending_maximize) {
                v2i resized = {0};
                SDL_GetWindowSize(ctx->window, &resized.x, &resized.y);
                CONFIG.windowSize = resized;
            }
        } else if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            pending_maximize = b_true;
        } else {
            pending_maximize = b_false;
        }
    } break;
    case SDL_MOUSEWHEEL: {
        mouseWheel.x = e.wheel.x;
        mouseWheel.y = e.wheel.y;
    } break;
    }
    const u8 *state = SDL_GetKeyboardState(NULL);
    memcpy(prevKeys, currentKeys, KEY_STATE_SIZE);
    memcpy(currentKeys, state, KEY_STATE_SIZE);
    prevMouse = currentMouse;
    prevMousePos = currentMousePos;
    currentMouse = SDL_GetMouseState(&currentMousePos.x, &currentMousePos.y);

    if (ctx->screen != NULL) {
        ctx->screen->update(ctx);
    }
}

void Game_render(Game *ctx) {
    SDL_FillRect(ctx->canvas, NULL,
                 SDL_MapRGB(ctx->canvas->format, 60, 60, 60));
    if (ctx->screen != NULL) {
        ctx->screen->render(ctx);
    }
    SDL_UpdateTexture(ctx->texture, NULL, ctx->canvas->pixels,
                      ctx->canvas->pitch);

    v2i windowSize = {};
    SDL_GetWindowSize(ctx->window, &windowSize.x, &windowSize.y);
    v2i canvasSize = {ctx->canvas->w, ctx->canvas->h};
    v2f scale = {(f32)windowSize.x / (f32)canvasSize.x,
                 (f32)windowSize.y / (f32)canvasSize.y};
    f32 s = scale.x > scale.y ? scale.y : scale.x;

    i32rect dest =
        (i32rect){(v2i){windowSize.x / 2 - ((i32)(canvasSize.x * s) / 2),
                        windowSize.y / 2 - ((i32)(canvasSize.y * s) / 2)},
                  (v2i){canvasSize.x * s, canvasSize.y * s}};

    SDL_RenderClear(ctx->renderer);
    SDL_RenderCopy(ctx->renderer, ctx->texture, NULL, (SDL_Rect *)(&dest));
    SDL_RenderPresent(ctx->renderer);
}

void Game_run(Game *ctx) {
    if (CONFIG.maximized) {
        SDL_MaximizeWindow(ctx->window);
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Started game context\n");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Target frameTime is %dms\n",
                (i32)((1.f / CONFIG.targetFPS) * 1000));
    while (ctx->running) {
        timerOld = timerNow;
        Game_pollEvent(ctx);
        Game_render(ctx);
        i32 target = CONFIG.targetFPS;
        i32 delay = target == 0 ? 0 : (i32)((1.f / target) * 1000);
        if (delay > 0)
            SDL_Delay(delay);
        timerNow = SDL_GetTicks();
        frameTime = (timerNow - timerOld) * 0.001f;
        fps[fpsIndex] = (i32)(1.f / Game_getFrameTime());
        fpsIndex = (fpsIndex + 1) % fpsBufferSize;
    }
    Game_destroy(ctx);
}

bool_t Game_keyPressed(SDL_Scancode code) {
    return (currentKeys[code] && !prevKeys[code]);
}

bool_t Game_keyReleased(SDL_Scancode code) {
    return (!currentKeys[code] && prevKeys[code]);
}

bool_t Game_keyDown(SDL_Scancode code) { return (currentKeys[code]); }

bool_t Game_keyUp(SDL_Scancode code) { return (!currentKeys[code]); }

v2i Game_mousePos() { return currentMousePos; }
v2i Game_mouseDelta() {
    return (v2i){prevMousePos.x - currentMousePos.x,
                 prevMousePos.y - currentMousePos.y};
}

v2i Game_mouseWheel() { return mouseWheel; }

bool_t Game_mousePressed(i32 mouseButton) {
    return (currentMouse & SDL_BUTTON(mouseButton)) &&
           !(prevMouse & SDL_BUTTON(mouseButton));
}

bool_t Game_mouseReleased(i32 mouseButton) {
    return !(currentMouse & SDL_BUTTON(mouseButton)) &&
           (prevMouse & SDL_BUTTON(mouseButton));
}

bool_t Game_mouseDown(i32 mouseButton) {
    return (currentMouse & SDL_BUTTON(mouseButton));
}

bool_t Game_mouseUp(i32 mouseButton) {
    return !(currentMouse & SDL_BUTTON(mouseButton));
}

void Game_setScreen(Game *ctx, Screen *value) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Changing context screen...\n");
    if (ctx->screen != NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Screen is not NULL, Unloading previous value...\n");
        if (ctx->screen->unload != NULL) {
            ctx->screen->unload(ctx);
        }
        ctx->screen = NULL;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Setting new value...\n");
    ctx->screen = value;
    if (ctx->screen != NULL) {
        if (ctx->screen->load != NULL) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                        "Loading screen data...\n");
            ctx->screen->load(ctx);
        }
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Screen changed successfully\n");
}

i32 Game_getFPS() {
    i32 res = 0;
    for (i32 i = 0; i < fpsBufferSize; i++) {
        res += fps[i];
    }
    res /= fpsBufferSize;
    return res;
}

f32 Game_getTime() { return timerNow; }

void Game_setTargetFPS(i32 value) { CONFIG.targetFPS = value; }

f32 Game_getFrameTime() { return frameTime; }

void Game_setPixel(Game *ctx, v2u pos, u32 col) {
    if (pos.x >= ctx->canvas->w || pos.y >= ctx->canvas->h) {
        return;
    }
    SDL_Surface *surface = ctx->canvas;
    u32 *const target_pixel =
        (u32 *)((u8 *)surface->pixels + pos.y * surface->pitch +
                pos.x * surface->format->BytesPerPixel);
    *target_pixel = col;
}
