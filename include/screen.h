#pragma once

typedef struct Game Game;

typedef struct {
    void (*load)(Game *ctx);
    void (*unload)(Game *ctx);
    void (*update)(Game *ctx);
    void (*render)(Game *ctx);
} Screen;
