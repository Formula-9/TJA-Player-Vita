#ifndef TJA_PLAYER_VITA_STATE_H
#define TJA_PLAYER_VITA_STATE_H

#include "StateMachineCommand.h"
#include "StateMessage.h"

typedef StateMachineCommand (*StartFunction) (StateMessage *stateMessage);
typedef StateMachineCommand (*UpdateFunction)();
typedef StateMachineCommand (*EndFunction)   (StateMessage *stateMessage);

/* Forward declaration */
typedef struct State State;

/**
 * A State can basically be representated as a screen in an application.
 * For instance, a screen where you can select an option that brings
 * another screen.
 * @var startFunction: Returns a StateMachineCommand, requires a StateMessage. Called by
 * the StateMachine on state change or application start. Data may be read from the StateMessage.
 * @var updateFunction: Returns a StateMachineCommand, requires a SDL_Renderer. Called every
 * loop by the StateMachine, the main logic should go in this function.
 * @var endFunction: Returns a StateMachineCommand, requires a StateMessage. Called by the
 * StateMachine, data may be written to the StateMessage.
 * @var nextState: A pointer to an instance of State that should be started on State change.
 */
struct State {
    StartFunction  startFunction;
    UpdateFunction updateFunction;
    EndFunction    endFunction;
    State          *nextState;
};

#endif //TJA_PLAYER_VITA_STATE_H
