#pragma once

typedef struct _screen {
    void (*load)();
    void (*unload)();
    void (*update)();
    void (*draw)();
} Screen;
