#include "config.h"
#include <raylib.h>

GameConfiguration CONFIG = CONFIG_DEFAULT;

char *Config_toCString(GameConfiguration config, size_t *size) {
    size_t bufferSize = CONFIG_MAX_SYMBOLS * sizeof(char);
    char *buffer = (char *)MemAlloc(bufferSize);

    sprintf_s(buffer, bufferSize, "%s\n%d\n%d\n%d\n%d\n",
              config.title, config.window_width, config.window_height,
              config.targetFPS, config.maximized);
    return buffer;
}

void Config_Save() {
    size_t size;
    char *conf = Config_toCString(CONFIG, &size);
    SaveFileText(CONFIG_PATH, conf);
    MemFree(conf);
}

void Config_Parse() {
    size_t bufferSize = CONFIG_MAX_SYMBOLS * sizeof(char);
    char *buffer = (char *)MemAlloc(bufferSize);

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

char* Config_getUserSavesDir() {
    char *env = getenv("USERPROFILE");
	int pos = TextLength(env);
    TextAppend(env, "\\Documents\\My Games\\roga\\", &pos);
    return env;
}
