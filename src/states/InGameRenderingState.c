#include "../../include/Logger.h"
#include "../../include/states/InGameRenderingState.h"

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <psp2/types.h>

static vita2d_texture *topBgSprite;
static vita2d_texture *laneLeftWindowSprite;
static vita2d_texture *noteLaneSprite;
static vita2d_texture *hitMarkSprite;
static SceCtrlData ctrl;

void inGameRenderingStateStart() {
    initTopBg();
    initLaneLeftWindow();
    initNoteLane();
    initHitMark();
    inGameRenderingStateUpdate();
}

void inGameRenderingStateUpdate() {
    do {
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        drawTopBg();
        drawNoteLane();
        drawHitMark();
        drawLaneLeftWindow();
    } while (ctrl.buttons & SCE_CTRL_START);
    inGameRenderingStateEnd();
}

void inGameRenderingStateEnd() {
    vita2d_free_texture(topBgSprite);
    vita2d_free_texture(laneLeftWindowSprite);
    vita2d_free_texture(noteLaneSprite);
    vita2d_free_texture(hitMarkSprite);
}

void initTopBg() {
    //SDL_Rect dimRect = { .x = 0, .y = 0, .w = 278, .h = 156 };
    topBgSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/bg_top_0.png");
    if (!topBgSprite) { writeToLogger("Error: Couldn't load the top BG!"); }
}

void initLaneLeftWindow() {
    /* SDL_Rect dstRect = { .x = 0, .y = 148, .w = 250, .h = 148 }; */
    laneLeftWindowSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/lane_left_window.png");
    if (!laneLeftWindowSprite) { writeToLogger("Error: Couldn't load the left lane window!"); }
}

void initNoteLane() {
    noteLaneSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/note_lane.png");
    if (!noteLaneSprite) { writeToLogger("Error: Couldn't load the note lane!"); }
}

void initHitMark() {
    hitMarkSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/hit_mark.png");
    if (!hitMarkSprite) { writeToLogger("Error: Couldn't load the hit mark!"); }
}

void drawTopBg() {
    for (int i = 0; i < 4; i++) {
        vita2d_draw_texture_part(topBgSprite, (i * 278), 0, 0, 0, 278, 156);
    }
}

void drawLaneLeftWindow() {
    vita2d_draw_texture(laneLeftWindowSprite, 0, 148);
}

void drawNoteLane() {
    vita2d_draw_texture_part(noteLaneSprite, 250, 148, 0, 0, 710, 140);
}

void drawHitMark() {
    vita2d_draw_texture(hitMarkSprite, 270, 164);
}