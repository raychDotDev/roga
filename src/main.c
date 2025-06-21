#include "assetLoader.h"
#include <game.h>

int main() {
    Game_Init();
	ResourceLoader_LoadFont();
    Game_Run();
    return 0;
}
