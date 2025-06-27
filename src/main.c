#include "config.h"
#include "typedef.h"
#define SDL_MAIN_HANDLED
#include "game.h"
#include <SDL2/SDL.h>

int wmain() {
    Config_load();
    Game *game = Game_new(CONFIG.title, CONFIG.windowSize, CONFIG.canvasSize);
    Game_run(game);
    Config_save();
    return 0;
}
