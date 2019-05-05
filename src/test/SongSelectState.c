#include "../../include/states/SongSelectState.h"

State songSelectState = { .startFunction = &songSelectStateStart,
                          .updateFunction = &songSelectStateUpdate,
                          .endFunction = &songSelectStateEnd,
                          .nextState = NULL };

static SongSelectState stateData = { .selectedDifficulty = DIFFICULTY_NORMAL };

StateMachineCommand songSelectStateStart(StateMessage *stateMessage) {
    initAllBg();
    return STATE_MACHINE_COMMAND_RUN_STATE;
}

StateMachineCommand songSelectStateUpdate() {
    sceCtrlPeekBufferPositive(0, &stateData.ctrl, 1);
    handleButtons(stateData.ctrl);
    drawBg();
    return (stateData.ctrl.buttons & SCE_CTRL_START) ? STATE_MACHINE_COMMAND_END_GAME : STATE_MACHINE_COMMAND_RUN_STATE;;
}

StateMachineCommand songSelectStateEnd(StateMessage *stateMessage) {
    freeAllBg();
    return STATE_MACHINE_COMMAND_END_GAME;
}

void initAllBg() {
    stateData.songSelectBgEasy = vita2d_load_PNG_file(SONGSELECTSTATE_BG_EASY);
    if (!stateData.songSelectBgEasy) writeToLogger("Error: Couldn't load the song selection background for Easy charts!");

    stateData.songSelectBgNormal = vita2d_load_PNG_file(SONGSELECTSTATE_BG_NORMAL);
    if (!stateData.songSelectBgNormal) writeToLogger("Error: Couldn't load the song selection background for Normal charts!");

    stateData.songSelectBgHard = vita2d_load_PNG_file(SONGSELECTSTATE_BG_HARD);
    if (!stateData.songSelectBgHard) writeToLogger("Error: Couldn't load the song selection background for Hard charts!");

    stateData.songSelectBgOni = vita2d_load_PNG_file(SONGSELECTSTATE_BG_ONI);
    if (!stateData.songSelectBgOni) writeToLogger("Error: Couldn't load the song selection background for Oni charts!");
}

void freeAllBg() {
    vita2d_free_texture(stateData.songSelectBgEasy);
    vita2d_free_texture(stateData.songSelectBgNormal);
    vita2d_free_texture(stateData.songSelectBgHard);
    vita2d_free_texture(stateData.songSelectBgOni);
}

//TODO: The picture isn't well drawn... I guess it kinda works though with the default skin.
void drawBg() {
    switch (stateData.selectedDifficulty) {
        case DIFFICULTY_EASY:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(stateData.songSelectBgEasy, (i * 486), 0, 1, 0, 486, 550);
            break;
        case DIFFICULTY_NORMAL:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(stateData.songSelectBgNormal, (i * 486), 0, 1, 0, 486, 550);
            break;
        case DIFFICULTY_HARD:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(stateData.songSelectBgHard, (i * 486), 0, 1, 0, 486, 550);
            break;
        case DIFFICULTY_ONI:
            for (int i = 0; i < 2; i++) vita2d_draw_texture_part(stateData.songSelectBgOni, (i * 486), 0, 1, 0, 486, 550);
            break;
    }
}

void handleButtons() {
    if (stateData.ctrl.buttons & SCE_CTRL_UP) { raiseDifficulty(); }
    else if (stateData.ctrl.buttons & SCE_CTRL_DOWN) { lowerDifficulty(); }
}

void raiseDifficulty() {
    if (stateData.selectedDifficulty < DIFFICULTY_ONI) { stateData.selectedDifficulty++; }
    else { stateData.selectedDifficulty = DIFFICULTY_EASY; }
}

void lowerDifficulty() {
    if (stateData.selectedDifficulty > DIFFICULTY_EASY) { stateData.selectedDifficulty--; }
    else { stateData.selectedDifficulty = DIFFICULTY_ONI; }
}