#pragma once
#include "typedef.h"
#include <SDL2/SDL_events.h>

#define KEY_STATE_SIZE 512

typedef struct {
    u8 prevKeys[KEY_STATE_SIZE];
    u8 currentKeys[KEY_STATE_SIZE];
    u32 prevMouse;
    v2i prevMousePos;
    u32 currentMouse;
    v2i currentMousePos;
    v2i mouseWheel;
} InputHandler;

void InputHandler_init(InputHandler *ctx);

void InputHandler_update(InputHandler *ctx, SDL_Event e);
