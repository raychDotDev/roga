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
        int codepoints[512] = {0};
        for (int i = 0; i < 95; i++)
            codepoints[i] = 32 + i;
        for (int i = 0; i < 255; i++)
            codepoints[96 + i] = 0x400 + i;
        RES_FONT = LoadFontEx(path,32,codepoints, 512);
    } else {
        TraceLog(LOG_TRACE, "Font was not found, using default");
        RES_FONT = GetFontDefault();
    }
    MemFree(path);

    SetTextureFilter(RES_FONT.texture, TEXTURE_FILTER_POINT);
}

void ResourceLoader_UnloadFont() { UnloadFont(RES_FONT); }
