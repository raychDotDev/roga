#pragma once

#include <raylib.h>

typedef struct GuiButton {
    Vector2 position;
    Vector2 size;
	char* text;
	int fontSize;
	int pressed;
	int down;
	int released;
	int up;
	Color idleColor;
	Color activeColor;
} GuiButton;

void GUI_Button(GuiButton *button, Vector2 mousePosition);

typedef struct GuiChechbox {
	Vector2 position;
	Vector2 size;
	int checked;
	Color uncheckedColor;
	Color checkedColor;
} GuiChechbox;

void GUI_Checkbox(GuiChechbox *checkbox, Vector2 mousePosition);
