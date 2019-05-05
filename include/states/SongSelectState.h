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

void initTriggerSprites();
void freeTriggerSprites();
void drawTriggerSprites();

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
    vita2d_texture *lTriggerSprite;
    vita2d_texture *rTriggerSprite;
    int selectedDifficulty;
    int currentSongIndex; //*2
    SceCtrlData ctrl;
} SongSelectState;

//*2: 0 = Random; 1 = Folder 0 / Song 0; Folder_0.SongNumber = Folder 1 / Song 0

#endif //TJA_PLAYER_VITA_SONGSELECTSTATE_H
