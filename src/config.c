#include "config.h"
#include <raylib.h>

GameConfiguration CONFIG = CONFIG_DEFAULT;

const char *Config_getConfigPath() {
    const char *dir = Config_getUserConfigDir();
    char *relativeConfig = ".rogaconfig";
    return TextFormat("%s%s", dir, relativeConfig);
}

const char *Config_getUserConfigDir() {
    char *env = getenv("USERPROFILE");
    return TextFormat("%s%s", env, "\\Documents\\My Games\\roga\\");
}

char *Config_toCString(GameConfiguration config, size_t *size) {
    size_t bufferSize = CONFIG_MAX_SYMBOLS * sizeof(char);
    char *buffer = (char *)MemAlloc(bufferSize);

    sprintf_s(buffer, bufferSize, "%s\n%d\n%d\n%d\n%d\n", config.title,
              config.windowWidth, config.windowHeight, config.targetFPS,
              config.maximized);
    return buffer;
}

void Config_Save() {
    size_t size;
    char *conf = Config_toCString(CONFIG, &size);
    const char *path = Config_getConfigPath();
    SaveFileText(path, conf);
    MemFree(conf);
}

void Config_Parse() {
    size_t bufferSize = CONFIG_MAX_SYMBOLS * sizeof(char);
    char *buffer = (char *)MemAlloc(bufferSize);
    const char *path = Config_getConfigPath();
    if (FileExists(path)) {
        strcpy(buffer, LoadFileText(path));
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
    conf.windowWidth = TextToInteger(parsed[1]);
    conf.windowHeight = TextToInteger(parsed[2]);
    conf.targetFPS = TextToInteger(parsed[3]);
    conf.maximized = TextToInteger(parsed[4]);

    MemFree(buffer);

    CONFIG = conf;
}
