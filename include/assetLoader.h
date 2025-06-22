#pragma once

#include <raylib.h>

static const char* RESOURCE_DIR = "./assets/";
static const char* FONTS_DIR = "fonts/";

extern Font RES_FONT;

void ResourceLoader_LoadFont();
void ResourceLoader_UnloadFont();
