#include "InGameRenderingState.h"

//Lane start Rect: x = 250, y = 148
State inGameRenderingState = { .startFunction = &inGameRenderingState_Start,
                               .updateFunction = &inGameRenderingState_Update,
                               .endFunction = &inGameRenderingState_End,
                               .nextState = NULL };

StateMachineCommand inGameRenderingState_Start(StateMessage *stateMessage) {
    initTopBg();
    initLaneLeftWindow();
    initNoteLane();
    initHitMark();
    return STATE_MACHINE_COMMAND_RUN_STATE;
}

StateMachineCommand inGameRenderingState_Update() {
    sceCtrlPeekBufferPositive(0, &stateData.ctrl, 1);
    drawTopBg();
    drawNoteLane();
    drawHitMark();
    drawLaneLeftWindow();
    return (stateData.ctrl.buttons & SCE_CTRL_START) ? STATE_MACHINE_COMMAND_END_GAME : STATE_MACHINE_COMMAND_RUN_STATE;
}

StateMachineCommand inGameRenderingState_End(StateMessage *stateMessage) {
    vita2d_free_texture(stateData.topBgSprite);
    vita2d_free_texture(stateData.laneLeftWindowSprite);
    vita2d_free_texture(stateData.noteLaneSprite);
    vita2d_free_texture(stateData.hitMarkSprite);
    return STATE_MACHINE_COMMAND_END_GAME;
}

void initTopBg() {
    //SDL_Rect dimRect = { .x = 0, .y = 0, .w = 278, .h = 156 };
    stateData.topBgSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/bg_top_0.png");
    if (stateData.topBgSprite == NULL) { writeToLogger("Error: Couldn't load the top BG!"); }
}

void initLaneLeftWindow() {
    /* SDL_Rect dstRect = { .x = 0, .y = 148, .w = 250, .h = 148 }; */
    stateData.laneLeftWindowSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/lane_left_window.png");
    if (stateData.laneLeftWindowSprite == NULL) { writeToLogger("Error: Couldn't load the left lane window!"); }
}

void initNoteLane() {
    stateData.noteLaneSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/note_lane.png");
    if (stateData.noteLaneSprite == NULL) { writeToLogger("Error: Couldn't load the note lane!"); }
}

void initHitMark() {
    stateData.hitMarkSprite = vita2d_load_PNG_file("ux0:/data/tjapvita/gfx/hit_mark.png");
    if (stateData.hitMarkSprite == NULL) { writeToLogger("Error: Couldn't load the hit mark!"); }
}

void drawTopBg() {
    for (int i = 0; i < 4; i++) {
        vita2d_draw_texture_part(stateData.topBgSprite, (i * 278), 0, 0, 0, 278, 156);
    }
}

void drawLaneLeftWindow() {
    vita2d_draw_texture(stateData.laneLeftWindowSprite, 0, 148);
}

void drawNoteLane() {
    vita2d_draw_texture_part(stateData.noteLaneSprite, 250, 148, 0, 0, 710, 140);
}

void drawHitMark() {
    vita2d_draw_texture(stateData.hitMarkSprite, 270, 164);
}
