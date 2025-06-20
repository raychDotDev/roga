#pragma once

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct GameConfiguration {
    char title[64];

    int window_width;
    int window_height;

    int targetFPS;

    int maximized;

} GameConfiguration;

static const GameConfiguration CONFIG_DEFAULT = {
    .title = "Game",
    .window_width = 720,
    .window_height = 480,
    .targetFPS = 120,
    .maximized = 0,
};

static const int CONFIG_MEMBER_COUNT = 5;

extern GameConfiguration CONFIG;

static const size_t CONFIG_MAX_SYMBOLS = 512;

static const char *CONFIG_PATH = "./.rogaconfig";

char *config_tocstring(GameConfiguration config, size_t *size);
void config_save();
void config_parse();
