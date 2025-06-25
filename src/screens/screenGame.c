#include "screens/screenGame.h"
#include "screens/screenMain.h"
#include "assetLoader.h"
#include "screens/screen.h"
#include "sprite.h"
#include <raylib.h>

Sprite test = {};

Texture tex;
void ScreenGame_load() {
    ResourceLoader_getTexture(SPRITE_TEST_KEY, &tex);
    Sprite_fromTexture(tex, 13, 21, 6, WHITE, &test);
    Sprite_play(&test);
}

void ScreenGame_draw() {
    Rectangle rec = Sprite_getFrameRec(&test);
    Sprite_drawSeq(&test, (Rectangle){0, 0, rec.width, rec.height}, 0.f,
                   SPRITE_SEQ_TEST, 7);
}

void ScreenGame_update() {
    Sprite_update(&test);
    if (test.end) {
        test.end = 0;
        test.currentFrame = 0;
        // Sprite_play(&test);
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (test.playing)
            Sprite_stop(&test);
        else
            Sprite_play(&test);
    }
    if (IsKeyReleased(KEY_ENTER)) {
        if (!test.playing)
            Sprite_play(&test);
        else
            Sprite_stop(&test);
    }
    if (IsKeyPressed(KEY_SPACE)) {
        Game_setCurrentScreen(ScreenMain_get());
    }
}

Screen *ScreenGame_get() {
    Screen *target = MemAlloc(sizeof(Screen));
    target->draw = ScreenGame_draw;
    target->load = ScreenGame_load;
    target->update = ScreenGame_update;
    return target;
}
