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
    InitWindow(CONFIG_DEFAULT.windowWidth, CONFIG_DEFAULT.windowHeight, CONFIG_DEFAULT.title);
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
    SetTraceLogLevel(LOG_ALL);
}

void Game_toggleMaximized() {
    maximized = !maximized;
    CONFIG.maximized = maximized;
}

void PreGameLoop();
void PostGameLoop();

void Game_Run() {
	PreGameLoop();
    while (running && !WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
        {
            Game_Draw();
        }
        EndDrawing();
        Game_Update();
    }
	PostGameLoop();

    CloseWindow();
}

void PreGameLoop() {
	ResourceLoader_LoadFont();
}
void PostGameLoop() {
    Config_Save();
	ResourceLoader_UnloadFont();
}

void Game_Draw() {
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
