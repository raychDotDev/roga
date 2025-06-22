#include "screenMain.h"
#include "game.h"

int main() {
    Game_init();
    Game_setCurrentScreen(ScreenMain_get());
    Game_run();
    return 0;
}
