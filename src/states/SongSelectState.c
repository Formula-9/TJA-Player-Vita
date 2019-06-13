#include <vita2d.h>
#include <psp2/io/fcntl.h>
#include <psp2/ctrl.h>
#include <psp2/types.h>

#include "../../include/Logger.h"
#include "../../include/Constants.h"
#include "../../include/states/SongSelectState.h"

static vita2d_texture *songSelectBgOni;
static vita2d_texture *songSelectBgHard;
static vita2d_texture *songSelectBgNormal;
static vita2d_texture *songSelectBgEasy;
static vita2d_texture *lTriggerSprite;
static vita2d_texture *rTriggerSprite;
static int selectedDifficulty;
//static int currentSongIndex; //*2
static SceCtrlData ctrl;

void initAllBg() {
    songSelectBgEasy = vita2d_load_PNG_file(SONGSELECTSTATE_BG_EASY);
    if (!songSelectBgEasy) writeToLogger("Error: Couldn't load the song selection background for Easy charts!");

    songSelectBgNormal = vita2d_load_PNG_file(SONGSELECTSTATE_BG_NORMAL);
    if (!songSelectBgNormal) writeToLogger("Error: Couldn't load the song selection background for Normal charts!");

    songSelectBgHard = vita2d_load_PNG_file(SONGSELECTSTATE_BG_HARD);
    if (!songSelectBgHard) writeToLogger("Error: Couldn't load the song selection background for Hard charts!");

    songSelectBgOni = vita2d_load_PNG_file(SONGSELECTSTATE_BG_ONI);
    if (!songSelectBgOni) writeToLogger("Error: Couldn't load the song selection background for Oni charts!");
}

void freeAllBg() {
    vita2d_free_texture(songSelectBgEasy);
    vita2d_free_texture(songSelectBgNormal);
    vita2d_free_texture(songSelectBgHard);
    vita2d_free_texture(songSelectBgOni);
}

//TODO: The picture isn't well drawn... I guess it kinda works though with the default skin.
void drawBg() {
    switch (selectedDifficulty) {
        case DIFFICULTY_EASY:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(songSelectBgEasy, (i * 486), 0, 1, 0, 486, 550);
            break;
        case DIFFICULTY_NORMAL:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(songSelectBgNormal, (i * 486), 0, 1, 0, 486, 550);
            break;
        case DIFFICULTY_HARD:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(songSelectBgHard, (i * 486), 0, 1, 0, 486, 550);
            break;
        case DIFFICULTY_ONI:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(songSelectBgOni, (i * 486), 0, 1, 0, 486, 550);
            break;
    }
}

void initTriggerSprites() {
    lTriggerSprite = vita2d_load_PNG_file(SONGSELECTSTATE_LTRIGGER_SPRITE);
    if (!lTriggerSprite) writeToLogger("Couldn't load L Trigger Sprite!");
    rTriggerSprite = vita2d_load_PNG_file(SONGSELECTSTATE_RTRIGGER_SPRITE);
    if (!rTriggerSprite) writeToLogger("Couldn't load R Trigger Sprite!");
}
void freeTriggerSprites() {
    vita2d_free_texture(lTriggerSprite);
    vita2d_free_texture(rTriggerSprite);
}

void drawTriggerSprites() {
    vita2d_draw_texture(lTriggerSprite, 243, 5);
    vita2d_draw_texture(rTriggerSprite, 643, 5);
}

void handleButtons() {
    if (ctrl.buttons & SCE_CTRL_UP) { raiseDifficulty(); }
    else if (ctrl.buttons & SCE_CTRL_DOWN) { lowerDifficulty(); }
}

void raiseDifficulty() {
    if (selectedDifficulty < DIFFICULTY_ONI) { selectedDifficulty++; }
    else { selectedDifficulty = DIFFICULTY_EASY; }
}

void lowerDifficulty() {
    if (selectedDifficulty > DIFFICULTY_EASY) { selectedDifficulty--; }
    else { selectedDifficulty = DIFFICULTY_ONI; }
}

void songSelectStateStart() {
    initAllBg();
    initTriggerSprites();
    songSelectStateUpdate();
}

void songSelectStateUpdate() {
    do {
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        handleButtons(ctrl);
        drawBg();
        drawTriggerSprites();
    } while (ctrl.buttons & SCE_CTRL_START);
    songSelectStateEnd();
}

void songSelectStateEnd() {
    freeAllBg();
    freeTriggerSprites();
}