#pragma once

#include "screen.h"
#include <raylib.h>

// use AFTER Game_Init, so you will be able to 
// load some GPU shit on screen->load()
void Game_setCurrentScreen(Screen* value);

// returns mouse position relative to canvas
Vector2 Game_getMouseCanvasPosition();

// Init game window, parse config and use it's value
// to set window parameters
void Game_init();

// Run the gameloop
void Game_run();

// Stop the gameloop
void Game_stop();

// Toggle maximize window
void Game_toggleMaximized();
