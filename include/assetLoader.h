#pragma once

#include <raylib.h>

static const char *RESOURCE_DIR = "./assets/";
static const char *FONTS_DIR = "fonts/";
static const char *TEXTURES_DIR = "textures/";

extern Font RES_FONT;

void ResourceLoader_loadFont();

void ResourceLoader_loadTextures();
void ResourceLoader_unloadTextures();
int ResourceLoader_getTexture(const char *key, Texture *out);

void ResourceLoader_unloadFont();
