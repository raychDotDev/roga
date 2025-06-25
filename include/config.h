#pragma once

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _gameConfig {
    char title[64];

    int windowWidth;
    int windowHeight;

    int targetFPS;

    int maximized;
} GameConfiguration;

// Default game configuration
static const GameConfiguration CONFIG_DEFAULT = {
    .title = "Game",
    .windowWidth = 320,
    .windowHeight = 200,
    .targetFPS = 120,
    .maximized = 0,
};

// %USERPROFILE%/Documents/roga
const char *Config_getUserConfigDir();

// %USERPROFILE%/Documents/roga/.rogaconfig
const char* Config_getConfigPath();

// GameConfiguration struct member count
static const int CONFIG_MEMBER_COUNT = 5;

// Global configuration
extern GameConfiguration CONFIG;

// Max simbols for .rogaconfig
static const size_t CONFIG_MAX_SYMBOLS = 512;

// Writes global configuration into .rogaconfig file
void Config_Save();

// Reads config file from user config dir 
// and sets global configuration to it's value.
// If there's no such file, returns CONFIG_DEFAULT.
void Config_Parse();
