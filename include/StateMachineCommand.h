#ifndef TJA_PLAYER_VITA_STATEMACHINECOMMAND_H
#define TJA_PLAYER_VITA_STATEMACHINECOMMAND_H

/**
 * Commands for the StateMachine.
 */
typedef enum StateMachineCommand {
    STATE_MACHINE_COMMAND_INIT         = 0,
    STATE_MACHINE_COMMAND_RUN_STATE    = 1,
    STATE_MACHINE_COMMAND_CHANGE_STATE = 2,
    STATE_MACHINE_COMMAND_END_GAME     = 3,
} StateMachineCommand;

#endif //TJA_PLAYER_VITA_STATEMACHINECOMMAND_H