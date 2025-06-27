#include "game.h"
#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

Game *Game_new(const char *title, v2i size, v2i canvasSize) {
    Game *game = (Game *)malloc(sizeof(Game));
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
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow Error: %s\n",
                     SDL_GetError());
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Initialized window successfully\n");
    }

    game->renderer =
        SDL_CreateRenderer(game->window, -1, SDL_RENDERER_SOFTWARE);
    if (game->renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer Error: %s\n",
                     SDL_GetError());
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Renderer initialized successfully\n");
    }

    game->canvas =
        SDL_CreateRGBSurface(0, canvasSize.x, canvasSize.y, 32, 0, 0, 0, 0);
    game->texture = SDL_CreateTextureFromSurface(game->renderer, game->canvas);
    game->running = b_true;
    return game;
}

void Game_destroy(Game *ctx) {
    SDL_FreeSurface(ctx->canvas);
    SDL_DestroyTexture(ctx->texture);
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    free(ctx);
    SDL_Quit();
}

void Game_stop(Game *ctx) { ctx->running = b_false; }

void Game_changeCanvasSize(Game *ctx, v2i size) {
    SDL_FreeSurface(ctx->canvas);
    SDL_DestroyTexture(ctx->texture);
    ctx->canvas = SDL_CreateRGBSurface(0, size.x, size.y, 32, 0, 0, 0, 0);
    ctx->texture = SDL_CreateTextureFromSurface(ctx->renderer, ctx->canvas);
    CONFIG.canvasSize = size;
}

void Game_pollEvent(Game *ctx) {
    SDL_Event e;
    SDL_PollEvent(&e);
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
    }
}

void Game_run(Game *ctx) {
    if (CONFIG.maximized) {
        SDL_MaximizeWindow(ctx->window);
    }
    while (ctx->running) {
        Game_pollEvent(ctx);
        SDL_FillRect(ctx->canvas, NULL,
                     SDL_MapRGB(ctx->canvas->format, 60, 60, 60));

        // TODO: Draw stuff

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
    Game_destroy(ctx);
}
