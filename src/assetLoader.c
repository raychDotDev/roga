#include "assetLoader.h"
#include <raylib.h>
#include <string.h>

Font RES_FONT;

void ResourceLoader_loadFont() {
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
        RES_FONT = LoadFontEx(path, 32, codepoints, 512);
    } else {
        TraceLog(LOG_TRACE, "Font was not found, using default");
        RES_FONT = GetFontDefault();
    }
    MemFree(path);

    SetTextureFilter(RES_FONT.texture, TEXTURE_FILTER_POINT);
}

const int MAX_TEXTURES_COUNT = 256;

typedef struct TextureMapMember {
    const char *key;
    int keysize;
    Texture texture;
} TextureMapMember;

TextureMapMember *textureMap;
int textureMapCount;

void ResourceLoader_loadTextures() {
    textureMap = MemAlloc(MAX_TEXTURES_COUNT * sizeof(TextureMapMember));
    textureMapCount = 0;

    TraceLog(LOG_TRACE, "Loading textures...");
    char *path = (char *)MemAlloc(128 * sizeof(char));
    int pos = 0;
    TextAppend(path, RESOURCE_DIR, &pos);
    TextAppend(path, TEXTURES_DIR, &pos);
    FilePathList list = LoadDirectoryFiles(path);
    MemFree(path);

    if (list.count == 0) {
        TraceLog(LOG_TRACE, "No textures in textures path, stopping...");
        return;
    }
    for (int i = 0; i < list.count; i++) {
        if (textureMapCount == MAX_TEXTURES_COUNT) {
            TraceLog(LOG_TRACE, "TextureMap reached max capacity, stopping...");
            break;
        }
        const char *ext = GetFileExtension(list.paths[i]);
        if (TextIsEqual(ext, ".png")) {
            int count;
            const char *keyExt = TextSplit(list.paths[i], '\\', &count)[1];
            const char *key = TextReplace(keyExt, ".png", "");
            textureMap[textureMapCount] = (TextureMapMember){
                .texture = LoadTexture(list.paths[i]),
                .key = key,
                .keysize = strlen(key),
            };
            textureMapCount++;
            TraceLog(LOG_TRACE, "Loaded texture with key %s", key);
        }
    }
    TraceLog(LOG_TRACE, "Loaded %d textures", textureMapCount);
}

void ResourceLoader_unloadTextures() {
    TraceLog(LOG_TRACE, "Unloading textures...");
    for (int i = 0; i < textureMapCount; i++) {
        UnloadTexture(textureMap[i].texture);
        TraceLog(LOG_TRACE, "Unloaded texture with key %s", textureMap[i].key);
    }
    MemFree(textureMap);
    TraceLog(LOG_TRACE, "Textures unloaded!");
}

int ResourceLoader_getTexture(const char *key, Texture *out) {
    for (int i = 0; i < textureMapCount; i++) {
        if (TextIsEqual(textureMap[i].key, key)) {
            *out = textureMap[i].texture;
            return 1;
        }
    }
    return 0;
}

void ResourceLoader_unloadFont() { UnloadFont(RES_FONT); }
