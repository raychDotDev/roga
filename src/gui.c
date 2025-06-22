#include "gui.h"
#include "assetLoader.h"
#include <raylib.h>
#include <raymath.h>

const int LINE_WIDTH = 2;

void GUI_Button(GuiButton *button, Vector2 mousePosition) {

    Rectangle bounds = (Rectangle){
        button->position.x,
        button->position.y,
        button->size.x,
        button->size.y,
    };
    if (CheckCollisionPointRec(mousePosition, bounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            button->down = 1;
            button->up = 0;
        } else {
            button->down = 0;
            button->up = 1;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            button->pressed = 1;
        } else {
            button->pressed = 0;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            button->released = 1;
        } else {
            button->released = 0;
        }
    } else {
        button->up = 1;
        button->down = 0;
        button->pressed = 0;
        button->released = 0;
    }

    Vector2 textSize =
        MeasureTextEx(RES_FONT, button->text, button->fontSize, 0);
    int textposX = button->position.x + button->size.x / 2.f - textSize.x / 2.f;
    int textposY = button->position.y + button->size.y / 2.f - textSize.y / 2.f;
    if (button->up) {
        DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height,
                      button->activeColor);
        DrawRectangle(bounds.x + LINE_WIDTH, bounds.y + LINE_WIDTH,
                      bounds.width - LINE_WIDTH * 2,
                      bounds.height - LINE_WIDTH * 2, button->idleColor);
        DrawTextEx(RES_FONT, button->text,
                   (Vector2){(float)textposX, (float)textposY},
                   button->fontSize, 0, button->activeColor);
    } else if (button->down) {
        DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height,
                      button->idleColor);
        DrawRectangle(bounds.x + LINE_WIDTH, bounds.y + LINE_WIDTH,
                      bounds.width - LINE_WIDTH * 2,
                      bounds.height - LINE_WIDTH * 2, button->activeColor);
        DrawTextEx(RES_FONT, button->text,
                   (Vector2){(float)textposX, (float)textposY},
                   button->fontSize, 0, button->idleColor);
    }
}

void GUI_Checkbox(GuiChechbox *checkbox, Vector2 mousePosition) {
    Rectangle bounds = (Rectangle){
        checkbox->position.x,
        checkbox->position.y,
        checkbox->size.x,
        checkbox->size.y,
    };
    Rectangle halfBounds = (Rectangle){
        checkbox->position.x + checkbox->size.x / 2 - checkbox->size.x / 4,
        checkbox->position.y + checkbox->size.y / 2 - checkbox->size.y / 4,
        checkbox->size.x / 2,
        checkbox->size.y / 2,
    };
    if (CheckCollisionPointRec(mousePosition, bounds)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            checkbox->checked = !checkbox->checked;
        }
    }
    if (checkbox->checked) {
        DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height,
                      checkbox->checkedColor);
        DrawRectangle(bounds.x + LINE_WIDTH, bounds.y + LINE_WIDTH,
                      bounds.width - LINE_WIDTH * 2,
                      bounds.height - LINE_WIDTH * 2, checkbox->uncheckedColor);
        DrawRectangle(halfBounds.x, halfBounds.y, halfBounds.width,
                      halfBounds.height, checkbox->checkedColor);
    } else {
        DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height,
                      checkbox->uncheckedColor);
        DrawRectangle(bounds.x + LINE_WIDTH, bounds.y + LINE_WIDTH,
                      bounds.width - LINE_WIDTH * 2,
                      bounds.height - LINE_WIDTH * 2, checkbox->checkedColor);
        DrawRectangle(halfBounds.x, halfBounds.y, halfBounds.width,
                      halfBounds.height, checkbox->uncheckedColor);
    }
}
