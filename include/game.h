#pragma once

#include "screen.h"

// use AFTER Game_Init, so you will be able to 
// load some GPU shit on screen->load()
void Game_setCurrentScreen(Screen* value);

// Init game window, parse config and use it's value
// to set window parameters
void Game_init();

// Run the gameloop
void Game_run();

// Stop the gameloop
void Game_stop();

// Toggle maximize window
void Game_toggleMaximized();
