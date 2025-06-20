#include "game.h"
#include "config.h"
#include <raylib.h>

int prevWindowWidth;
int prevWindowHeight;

int maximized = 0;

int running = 1;

void Game_Init() {
    InitWindow(640, 320, "game");
    Config_Parse();
    Config_Save();
    SetWindowSize(CONFIG.window_width, CONFIG.window_height);
    SetWindowTitle(CONFIG.title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(CONFIG.targetFPS);
	char* saves_path = Config_getUserSavesDir();
	MakeDirectory(saves_path);
    if (CONFIG.maximized) {
        MaximizeWindow();
    }
    SetExitKey(KEY_NULL);
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

void Game_Draw() { DrawFPS(10, 10); }

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
            CONFIG.window_width = prevWindowWidth;
            CONFIG.window_height = prevWindowHeight;
        }
    }
}

void Game_Stop() { running = 0; }
