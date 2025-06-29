#define SDL_MAIN_HANDLED

#include "data/screenMain.h"
#include "screen.h"
#include "game.h"
#include <SDL2/SDL.h>

int wmain() {
    Game *game = Game_new();
	if (game == NULL)
		return -1;
    Screen sm;
    ScreenMain_get(&sm);
    Game_setScreen(game, &sm);
    Game_run(game);
    return 0;
}
