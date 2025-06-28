#include "config.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* DATA_PATH = "\\Documents\\My Games\\roga\\";
static const char* CONF_PATH = ".rogaconfig";

Config CONFIG;
char *getConfigPath() {
    char *path = (char *)malloc(sizeof(char) * FILENAME_MAX);
    strcpy(path, getenv("USERPROFILE"));
    strcat(path, DATA_PATH);
    strcat(path, CONF_PATH);
    return path;
}

void Config_load() {
    char *path = getConfigPath();
    FILE *conf = fopen(path, "rb");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Loading config...\n");
    if (conf == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "No config file, setting defaults\n");
        CONFIG = CONFIG_DEFAULT;
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Reading config...\n");
        fread(&CONFIG, sizeof(Config), 1, conf);
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Config is loaded\n");
    }
    fclose(conf);
    free(path);
}

void Config_save() {
    char *path = getConfigPath();
    FILE *conf = fopen(path, "wb");
    fwrite(&CONFIG, sizeof(Config), 1, conf);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Config was saved to %s\n", path);
    fclose(conf);
    free(path);
}
