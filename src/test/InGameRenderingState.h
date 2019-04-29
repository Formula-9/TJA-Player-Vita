#ifndef TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H
#define TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H

#include "../State.h"
#include "../Logger.h"

#include <vita2d.h>
#include <psp2/ctrl.h>

StateMachineCommand inGameRenderingState_Start(StateMessage *stateMessage);
StateMachineCommand inGameRenderingState_Update();
StateMachineCommand inGameRenderingState_End(StateMessage *stateMessage);

/* Init */
void initTopBg();
void initLaneLeftWindow();
void initNoteLane();
void initHitMark();

/* Draw */
void drawTopBg();
void drawLaneLeftWindow();
void drawNoteLane();
void drawHitMark();

extern State inGameRenderingState;

typedef struct InGameRenderingState {
    vita2d_texture *topBgSprite;
    vita2d_texture *laneLeftWindowSprite;
    vita2d_texture *noteLaneSprite;
    vita2d_texture *hitMarkSprite;
    SceCtrlData ctrl;
} InGameRenderingState;

static InGameRenderingState stateData;

#endif //TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H
