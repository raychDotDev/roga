#include "config.h"
#include "data/screenMain.h"
#include "screen.h"

#define SDL_MAIN_HANDLED
#include "game.h"
#include <SDL2/SDL.h>

int wmain() {
    Config_load();
    Game *game = Game_new(CONFIG.title, CONFIG.windowSize, CONFIG.canvasSize);
    Screen sm;
    ScreenMain_get(&sm);
    Game_setScreen(game, &sm);
    Game_run(game);
    Config_save();
    return 0;
}
