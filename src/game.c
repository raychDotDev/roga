#include "game.h"
#include "config.h"
#include <raylib.h>

int prev_window_width;
int prev_window_height;

int maximized = 0;

int running = 1;

void init() {
    InitWindow(640, 320, "game");
    config_parse();
    config_save();
    SetWindowSize(CONFIG.window_width, CONFIG.window_height);
    SetWindowTitle(CONFIG.title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(CONFIG.targetFPS);
    if (CONFIG.maximized) {
        MaximizeWindow();
    }
    SetExitKey(KEY_NULL);
}

void toggle_maximized() {
    maximized = !maximized;
    CONFIG.maximized = maximized;
}

void run() {
    while (running && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        {
            draw();
        }
        EndDrawing();
        update();
    }
    config_save();
    CloseWindow();
}

void draw() { DrawFPS(10, 10); }

void update() {
    if ((!maximized && IsWindowMaximized()) ||
        (maximized && !IsWindowMaximized())) {
        toggle_maximized();
    }
    if (!maximized) {
        if (GetScreenWidth() != prev_window_width ||
            GetScreenHeight() != prev_window_height) {
            prev_window_width = GetScreenWidth();
            prev_window_height = GetScreenHeight();
            CONFIG.window_width = prev_window_width;
            CONFIG.window_height = prev_window_height;
        }
    }
}

void stop() { running = 0; }
