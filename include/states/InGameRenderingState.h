#ifndef TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H
#define TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H

#include "../StateMachineCommand.h"
#include "../State.h"
#include "../Logger.h"

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <psp2/types.h>

StateMachineCommand inGameRenderingStateStart(StateMessage *stateMessage);
StateMachineCommand inGameRenderingStateUpdate();
StateMachineCommand inGameRenderingStateEnd(StateMessage *stateMessage);

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

#endif //TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H
