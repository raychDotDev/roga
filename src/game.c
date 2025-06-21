#include "game.h"
#include "assetLoader.h"
#include "config.h"
#include "gui.h"
#include <raylib.h>

int prevWindowWidth;
int prevWindowHeight;

int maximized = 0;

int running = 1;

void Game_Draw();
void Game_Update();

void Game_Init() {
    InitWindow(640, 320, "game");
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
    const char *saves_path = Config_getUserConfigDir();
    MakeDirectory(saves_path);
    if (CONFIG.maximized) {
        MaximizeWindow();
    }
    SetExitKey(KEY_NULL);
    SetTraceLogLevel(LOG_ALL);
}

void Game_toggleMaximized() {
    maximized = !maximized;
    CONFIG.maximized = maximized;
}

void Game_Run() {
    while (running && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        {
            Game_Draw();
        }
        EndDrawing();
        Game_Update();
    }
    Config_Save();
    CloseWindow();
}

void Game_Draw() {
    DrawTextEx(RES_FONT, "HARRO", (Vector2){10, 10}, 20, 2, WHITE);
}

void Game_Update() {
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
}

void Game_Stop() { running = 0; }
