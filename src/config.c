#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <stdio.h>

static const char *CONF_PATH = ".rogaconfig";

void Config_load() {
    CONFIG = (Config *)malloc(sizeof(Config));

    FILE *conf = fopen(CONF_PATH, "rb");
    SDL_Log("Loading config...\n");
    if (conf == NULL) {
        SDL_Log("No config file, setting defaults\n");
        *CONFIG = CONFIG_DEFAULT;
    } else {
        SDL_Log("Reading config...\n");
        fread(CONFIG, sizeof(Config), 1, conf);
        SDL_Log("Config is loaded\n");
    }
    SDL_Log("READED VALS:\n"
            "\ttitle:%s\n"
            "\twinsize:%dx%d\n"
            "\tcanvassize:%dx%d\n"
            "\tmaximized:%d\n"
            "\ttargetFPS:%d\n",
            CONFIG->title, CONFIG->windowSize.x, CONFIG->windowSize.y,
            CONFIG->canvasSize.x, CONFIG->canvasSize.y, CONFIG->maximized,
            CONFIG->targetFPS);
    fclose(conf);
}

void Config_save() {
    FILE *conf = fopen(CONF_PATH, "wb");
    fwrite(CONFIG, sizeof(Config), 1, conf);
    SDL_Log("Config was saved\n");
    SDL_Log("SAVED VALS:\n"
            "\ttitle:%s\n"
            "\twinsize:%dx%d\n"
            "\tcanvassize:%dx%d\n"
            "\tmaximized:%d\n"
            "\ttargetFPS:%d\n",
            CONFIG->title, CONFIG->windowSize.x, CONFIG->windowSize.y,
            CONFIG->canvasSize.x, CONFIG->canvasSize.y, CONFIG->maximized,
            CONFIG->targetFPS);
    fclose(conf);
    free(CONFIG);
}
