#pragma once

#include "typedef.h"

typedef struct {
	const char* title;
	v2i windowSize;
	v2i canvasSize;
	bool_t maximized;
	i32 targetFPS;
} Config;

extern Config CONFIG;

static const Config CONFIG_DEFAULT = {
	.title = "roga",
	.windowSize = {720, 640},
	.canvasSize = {720, 640},
	.maximized = b_false,
	.targetFPS = 60,
};

void Config_load();
void Config_save();
