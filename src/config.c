#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Config CONFIG;
char* getConfigPath() {
    char *path = (char*)malloc(sizeof(char) * FILENAME_MAX);
    strcpy(path, getenv("USERPROFILE"));
    strcat(path, DATA_PATH);
    strcat(path, CONF_PATH);
	return path;
}

void Config_load() {
	char* path = getConfigPath();
    FILE* conf = fopen(path, "rb");
	if (conf == NULL) {
		CONFIG = CONFIG_DEFAULT;
	} else {
		fread(&CONFIG, sizeof(Config), 1, conf);
	}
	fclose(conf);
	free(path);
}

void Config_save() {
	char* path = getConfigPath();
	FILE* conf = fopen(path, "wb");
	fwrite(&CONFIG, sizeof(Config), 1, conf);
	fclose(conf);
	free(path);
}
