#include "data/screenMapEdit.h"
#include <string.h>
#define SDL_MAIN_HANDLED

#include "data/screenMain.h"
#include "game.h"
#include "screen.h"
#include <SDL2/SDL.h>

int wmain(i32 argc, char **argv) {
    Game *game = Game_new();
    if (game == NULL)
        return -1;
    Screen sm;
    if (argc > 1 && strcmp(argv[1], "--mapedit")) {
        ScreenMapEdit_get(&sm);
    } else {
        ScreenMain_get(&sm);
    }
    Game_setScreen(game, &sm);
    Game_run(game);
    return 0;
}
