#include "screens/screenMain.h"
#include "game.h"
#include "gui.h"
#include "screens/screen.h"
#include "screens/screenGame.h"
#include <raylib.h>

GuiButton button;

GuiChechbox checkbox;

Screen *ScreenMain_get() {
    Screen *target = MemAlloc(sizeof(Screen));

    target->load = ScreenMain_load;
    target->draw = ScreenMain_draw;
    target->update = ScreenMain_update;

    return target;
}

void ScreenMain_load() {
    button = (GuiButton){
        .position = {100, 100},
        .size = {100, 50},
        .text = "гойда!",
        .fontSize = GUI_FONTSIZE_DEFAULT,
        .activeColor = WHITE,
        .idleColor = BLACK,
    };
    checkbox = (GuiChechbox){
        .position = {200, 200},
        .size = {50, 50},
        .checkedColor = WHITE,
        .uncheckedColor = BLACK,
    };
}

void ScreenMain_draw() {
    GUI_Button(&button, Game_getMouseCanvasPosition());
    GUI_Checkbox(&checkbox, Game_getMouseCanvasPosition());
    if (checkbox.checked) {
        DrawRectangle(0, 0, 10, 10, RED);
    }
    if (button.down) {
        DrawRectangle(400, 400, 10, 10, BLUE);
    }
}

void ScreenMain_update() {
    if (IsKeyPressed(KEY_SPACE)) {
        Game_setCurrentScreen(ScreenGame_get());
    }
}
