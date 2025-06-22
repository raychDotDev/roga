#include "screens/screenGame.h"
#include "screens/screen.h"
#include <raylib.h>

Screen *ScreenGame_get() {
    Screen *target = MemAlloc(sizeof(Screen));
    target->draw = ScreenGame_draw;
    return target;
}

void ScreenGame_draw() { DrawRectangle(0, 0, 200, 200, BLUE); }
