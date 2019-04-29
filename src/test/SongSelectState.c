#include "SongSelectState.h"

State songSelectState = { .startFunction = &songSelectState_Start,
                               .updateFunction = &songSelectState_Update,
                               .endFunction = &songSelectState_End,
                               .nextState = NULL };

StateMachineCommand songSelectState_Start(StateMessage *stateMessage) {
    return STATE_MACHINE_COMMAND_END_GAME;
}

StateMachineCommand songSelectState_Update() {
    return STATE_MACHINE_COMMAND_END_GAME;
}

StateMachineCommand songSelectState_End(StateMessage *stateMessage) {
    return STATE_MACHINE_COMMAND_END_GAME;
}