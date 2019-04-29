#ifndef TJA_PLAYER_VITA_STATEMACHINE_H
#define TJA_PLAYER_VITA_STATEMACHINE_H

#include "StateMachineCommand.h"
#include "State.h"
#include "StateMessage.h"
#include "Logger.h"

/**
 * Represents a State Machine that loads States and receive commands from
 * manipulating them.
 * @var stateMachineCommand: The command to execute on the next loop.
 * @var stateMessage: A pointer to a StateMessage struct that contains data to transfer
 * from one State to another.
 * @var state: A pointer to the current State to execute.
 */
typedef struct StateMachine {
    StateMachineCommand stateMachineCommand;
    StateMessage stateMessage;
    State state;
} StateMachine;

void updateStateMachine(StateMachine *stateMachine);
void changeStateMachineState(StateMachine *stateMachine);
void cleanupStateMachine(StateMachine *stateMachine);

#endif //TJA_PLAYER_VITA_STATEMACHINE_H
