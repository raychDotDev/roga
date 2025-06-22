#pragma once

typedef struct Screen Screen;

typedef struct Screen {
    void (*load)();
    void (*unload)();
    void (*update)();
    void (*draw)();
} Screen;
