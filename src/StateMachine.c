#include "../include/Logger.h"
#include "../include/StateMachine.h"

/**
 * Update the StateMachine's internal data, and also update the State's
 * internal data as well if applicable.
 * @param stateMachine A pointer to the StateMachine to update.
 */
void updateStateMachine(StateMachine *stateMachine) {
    switch (stateMachine->stateMachineCommand) {
        case STATE_MACHINE_COMMAND_INIT:
            stateMachine->stateMachineCommand = stateMachine->state.startFunction(NULL);
            break;
        case STATE_MACHINE_COMMAND_RUN_STATE:
            stateMachine->stateMachineCommand = stateMachine->state.updateFunction();
            break;
        case STATE_MACHINE_COMMAND_CHANGE_STATE:
            changeStateMachineState(stateMachine);
            break;
        default:
            break;
    }
}

/**
 * Change the StateMachine's currently running State by terminating
 * the current one and starting the next one.
 * @param stateMachine The StateMachine that requires its state changed.
 */
void changeStateMachineState(StateMachine *stateMachine) {
    stateMachine->state.endFunction(&stateMachine->stateMessage);
    stateMachine->state = (*stateMachine->state.nextState);
    stateMachine->stateMachineCommand = stateMachine->state.startFunction(&stateMachine->stateMessage);
}

/**
 * Cleans up all the memory used by the StateMachine. Since this function
 * is likely to be called after the command becomes STATE_MACHINE_COMMAND_END_GAME,
 * it is assumed that the State's end function was called and the memory used by it
 * freed. Therefore, for now, only the StateMessage will be cleaned.
 * @param stateMachine A pointer to the StateMachine to clean.
 */
void cleanupStateMachine(StateMachine *stateMachine) {
    cleanupStateMessage(&stateMachine->stateMessage);
}