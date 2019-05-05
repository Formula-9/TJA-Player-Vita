#ifndef TJA_PLAYER_VITA_SONGSELECTSTATE_H
#define TJA_PLAYER_VITA_SONGSELECTSTATE_H

#include <vita2d.h>
#include <psp2/io/fcntl.h>
#include <psp2/ctrl.h>
#include <psp2/types.h>

#include "../StateMachineCommand.h"
#include "../State.h"
#include "../Logger.h"
#include "../Constants.h"

StateMachineCommand songSelectStateStart(StateMessage *stateMessage);
StateMachineCommand songSelectStateUpdate();
StateMachineCommand songSelectStateEnd(StateMessage *stateMessage);

// ================================================ //
// || Graphics-related functions                 || //
// ================================================ //
void initAllBg();
void freeAllBg();
void drawBg();

// ================================================ //
// || Controls & Difficulty Change               || //
// ================================================ //
void handleButtons();
void raiseDifficulty();
void lowerDifficulty();

extern State songSelectState;

typedef struct SongSelectState {
    vita2d_texture *songSelectBgOni;
    vita2d_texture *songSelectBgHard;
    vita2d_texture *songSelectBgNormal;
    vita2d_texture *songSelectBgEasy;
    int selectedDifficulty;
    SceCtrlData ctrl;
} SongSelectState;

#endif //TJA_PLAYER_VITA_SONGSELECTSTATE_H
