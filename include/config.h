#pragma once

#include "typedef.h"

static const char* DATA_PATH = "\\Documents\\My Games\\roga\\";
static const char* CONF_PATH = ".rogaconfig";

typedef struct {
	const char* title;
	v2i windowSize;
	v2i canvasSize;
	bool_t maximized;
} Config;

extern Config CONFIG;

static const Config CONFIG_DEFAULT = {
	.title = "roga",
	.windowSize = {720, 640},
	.canvasSize = {720, 640},
	.maximized = b_false,
};

void Config_load();
void Config_save();
