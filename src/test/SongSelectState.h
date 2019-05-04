#ifndef TJA_PLAYER_VITA_SONGSELECTSTATE_H
#define TJA_PLAYER_VITA_SONGSELECTSTATE_H

#include <vita2d.h>
#include <psp2/io/fcntl.h>
#include <psp2/ctrl.h>
#include <psp2/types.h>

#include "../../include/StateMachineCommand.h"
#include "../../include/State.h"
#include "../../include/Logger.h"

StateMachineCommand songSelectState_Start(StateMessage *stateMessage);
StateMachineCommand songSelectState_Update();
StateMachineCommand songSelectState_End(StateMessage *stateMessage);

extern State songSelectState;

/* typedef struct SongSelectState {
} SongSelectState;

static SongSelectState stateData; */

#endif //TJA_PLAYER_VITA_SONGSELECTSTATE_H
