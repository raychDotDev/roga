#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "app.h"

int wmain() { 
	Game *app = Game_new((v2i){800, 600}, (v2i){720, 480}); 
	Game_run(app);
	return 0;
}
