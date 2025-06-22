#include "game.h"
#include "assetLoader.h"
#include "config.h"
#include "screen.h"
#include <raylib.h>
#include <raymath.h>

RenderTexture canvas;

Screen *currentScreen = NULL;

int prevWindowWidth;
int prevWindowHeight;

int maximized = 0;

int running = 1;

void Game_draw();
void Game_update();
void preGameLoop();
void postGameLoop();

void Game_init() {
    InitWindow(CONFIG_DEFAULT.windowWidth, CONFIG_DEFAULT.windowHeight,
               CONFIG_DEFAULT.title);
    const char *saves_path = Config_getUserConfigDir();
    MakeDirectory(saves_path);
    Config_Parse();
    Config_Save();
    SetWindowSize(CONFIG.windowWidth, CONFIG.windowHeight);
    int sw = GetMonitorWidth(GetCurrentMonitor());
    int sh = GetMonitorHeight(GetCurrentMonitor());
    SetWindowPosition(sw / 2 - CONFIG.windowWidth / 2,
                      sh / 2 - CONFIG.windowHeight / 2);
    SetWindowTitle(CONFIG.title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(CONFIG.targetFPS);
    SetWindowMinSize(CONFIG_DEFAULT.windowWidth, CONFIG_DEFAULT.windowHeight);
    if (CONFIG.maximized) {
        MaximizeWindow();
    }
    SetExitKey(KEY_NULL);
    SetTraceLogLevel(LOG_TRACE & LOG_ERROR);
    preGameLoop();
}

void Game_toggleMaximized() {
    maximized = !maximized;
    CONFIG.maximized = maximized;
}

void preGameLoop() {
    canvas = LoadRenderTexture(CONFIG_DEFAULT.windowWidth,
                               CONFIG_DEFAULT.windowHeight);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
    ResourceLoader_loadFont();
    ResourceLoader_loadTextures();
}

void postGameLoop() {
    Game_setCurrentScreen(NULL);
    Config_Save();
    ResourceLoader_unloadFont();
    ResourceLoader_unloadTextures();
    UnloadRenderTexture(canvas);
}

Rectangle dest = {};
float scale = 1.f;
Vector2 Game_getMouseCanvasPosition() {
    Vector2 globalPos = GetMousePosition();
    globalPos.x -= dest.x;
    globalPos.y -= dest.y;
    globalPos.x /= scale;
    globalPos.y /= scale;
    return globalPos;
}
void Game_run() {
    while (running && !WindowShouldClose()) {
        BeginTextureMode(canvas);
        ClearBackground(DARKGRAY);
        {
            Game_draw();
        }

        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        {
            Rectangle source = {0, 0, canvas.texture.width,
                                -canvas.texture.height};
            float yScale = (float)GetScreenHeight() / canvas.texture.height;
            float xScale = (float)GetScreenWidth() / canvas.texture.width;
            scale = xScale > yScale ? yScale : xScale;
            float destWidth = canvas.texture.width * scale;
            float destHeight = canvas.texture.height * scale;

            dest = (Rectangle){(float)GetScreenWidth() / 2 - destWidth / 2,
                               (float)GetScreenHeight() / 2 - destHeight / 2,
                               destWidth, destHeight};
            DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.f,
                           WHITE);
        }
        EndDrawing();

        Game_update();
    }
    postGameLoop();

    CloseWindow();
}

void Game_draw() {
    if (currentScreen->draw != NULL)
        currentScreen->draw();
}

void Game_update() {
    if ((!maximized && IsWindowMaximized()) ||
        (maximized && !IsWindowMaximized())) {
        Game_toggleMaximized();
    }
    if (!maximized) {
        if (GetScreenWidth() != prevWindowWidth ||
            GetScreenHeight() != prevWindowHeight) {
            prevWindowWidth = GetScreenWidth();
            prevWindowHeight = GetScreenHeight();
            CONFIG.windowWidth = prevWindowWidth;
            CONFIG.windowHeight = prevWindowHeight;
        }
    }
    if (currentScreen->update != NULL)
        currentScreen->update();
}

void Game_stop() { running = 0; }

void Game_setCurrentScreen(Screen *value) {
    TraceLog(LOG_TRACE, "Setting screen...");
    if (currentScreen != NULL) {
        TraceLog(LOG_TRACE, "currentScreen is not NULL, unloading...");
        if (currentScreen->unload != NULL) {
            currentScreen->unload();
            TraceLog(LOG_TRACE, "currentScreen unloaded!");
        } else {
            TraceLog(LOG_TRACE, "currentScreen->unload is NULL, skipping...");
        }
        MemFree(currentScreen);
        currentScreen = NULL;
        TraceLog(LOG_TRACE, "currentScreen pointer is cleaned!");
    } else {
        TraceLog(LOG_TRACE, "currentScreen is NULL, skipping...");
    }

    currentScreen = value;

    TraceLog(LOG_TRACE, "currentScreen is set to new value, loading...");
    if (currentScreen != NULL) {
        if (currentScreen->load != NULL) {
            currentScreen->load();
            TraceLog(LOG_TRACE, "currentScreen loaded!");
        } else {
            TraceLog(LOG_TRACE, "currentScreen->load is NULL, skipping...");
        }
    } else {
        TraceLog(LOG_TRACE, "currentScreen is NULL, skipping...");
    }
    TraceLog(LOG_TRACE, "currentScreen is setted up!");
}
