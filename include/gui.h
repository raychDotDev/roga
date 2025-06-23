#pragma once

#include <raylib.h>

static const int GUI_FONTSIZE_DEFAULT = 8;

typedef struct _guiButton {
    Vector2 position;
    Vector2 size;
    char *text;
    int fontSize;
    int pressed;
    int down;
    int released;
    int up;
    Color idleColor;
    Color activeColor;
} GuiButton;

void GUI_Button(GuiButton *button, Vector2 mousePosition);

typedef struct _guiCheckbox {
    Vector2 position;
    Vector2 size;
    int checked;
    Color uncheckedColor;
    Color checkedColor;
} GuiChechbox;

void GUI_Checkbox(GuiChechbox *checkbox, Vector2 mousePosition);
