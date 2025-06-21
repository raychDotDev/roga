#include "assetLoader.h"
#include <raylib.h>

Font RES_FONT;

void ResourceLoader_LoadFont() {
    char *path = (char *)MemAlloc(128 * sizeof(char));
    int pos = 0;
    TextAppend(path, RESOURCE_DIR, &pos);
    TextAppend(path, FONTS_DIR, &pos);
    TextAppend(path, "font.ttf", &pos);
    if (FileExists(path)) {
		TraceLog(LOG_TRACE, "Font was found");
        RES_FONT = LoadFont(path);
    }
    MemFree(path);

	SetTextureFilter(RES_FONT.texture, TEXTURE_FILTER_POINT);
}
