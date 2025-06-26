#define SDL_MAIN_HANDLED
#include "game.h"
#include "string.h"
#include <SDL2/SDL.h>

int wmain() {
    Game *game = Game_new((v2i){800, 600}, (v2i){720, 480});
    Game_run(game);
    return 0;
}
