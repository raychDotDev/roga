#include "config.h"

GameConfiguration CONFIG = CONFIG_DEFAULT;

char *config_tocstring(GameConfiguration config, size_t *size) {
    size_t buffersize = CONFIG_MAX_SYMBOLS * sizeof(char);
    char *buffer = (char *)MemAlloc(buffersize);

    sprintf_s(buffer, buffersize, "%s\n%d\n%d\n%d\n%d\n",
              config.title, config.window_width, config.window_height,
              config.targetFPS, config.maximized);
    return buffer;
}

void config_save() {
    size_t size;
    char *conf = config_tocstring(CONFIG, &size);
    SaveFileText(CONFIG_PATH, conf);
    MemFree(conf);
}

void config_parse() {
    size_t buffersize = CONFIG_MAX_SYMBOLS * sizeof(char);
    char *buffer = (char *)MemAlloc(buffersize);

    if (FileExists(CONFIG_PATH)) {
        strcpy(buffer, LoadFileText(CONFIG_PATH));
    } else {
        CONFIG = CONFIG_DEFAULT;
        return;
    }
    int count;

    const char **parsed = TextSplit(buffer, '\n', &count);

    if (count < CONFIG_MEMBER_COUNT) {
        CONFIG = CONFIG_DEFAULT;
        return;
    }

    GameConfiguration conf = {};

    TextCopy(conf.title, parsed[0]);
    conf.window_width = TextToInteger(parsed[1]);
    conf.window_height = TextToInteger(parsed[2]);
    conf.targetFPS = TextToInteger(parsed[3]);
    conf.maximized = TextToInteger(parsed[4]);

    MemFree(buffer);

    CONFIG = conf;
}
