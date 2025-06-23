#include "screens/screenGame.h"
#include "assetLoader.h"
#include "screens/screen.h"
#include "sprite.h"
#include <raylib.h>

Sprite test = {};

Texture tex;
void ScreenGame_load() {
    ResourceLoader_getTexture(SPRITE_TEST_KEY, &tex);
    Sprite_fromTexture(tex, 13, 21, 12, WHITE, &test);
	Sprite_play(&test);
}

void ScreenGame_draw() {
    DrawTexturePro(tex, (Rectangle){0, 0, 14, 21},
                   (Rectangle){100, 100, 100, 100}, (Vector2){0, 0}, 0.f,
                   WHITE);
    Sprite_drawSeq(&test, (Rectangle){0, 0, 100, 100}, 0.f, SPRITE_SEQ_TEST, 7);
}

void ScreenGame_update() { 
	Sprite_update(&test); 
	if (test.end) {
		test.end = 0;
		test.currentFrame = 0;
		// Sprite_play(&test);
	}
}

Screen *ScreenGame_get() {
    Screen *target = MemAlloc(sizeof(Screen));
    target->draw = ScreenGame_draw;
    target->load = ScreenGame_load;
    target->update = ScreenGame_update;
    return target;
}
