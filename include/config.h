#pragma once

#include "typedef.h"
#define CONFIG_MAX_TITLE 64
typedef struct {
    char title[CONFIG_MAX_TITLE];
    v2i windowSize;
    v2i canvasSize;
    bool_t maximized;
    i32 targetFPS;
} Config;

extern Config *CONFIG;

static const Config CONFIG_DEFAULT = {
    .title = "Game",
    .windowSize = {720, 480},
    .canvasSize = {384, 216},
    .maximized = b_false,
    .targetFPS = 60,
};

void Config_load();
void Config_save();
