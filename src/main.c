#include <psp2/kernel/processmgr.h>
#include <vita2d.h>

#include "Logger.h"
#include "StateMachine.h"
#include "StateMachineCommand.h"
#include "test/InGameRenderingState.h"

int main() {
    vita2d_init();
    initializeLogger();

    //writeToLogger("Info: TJA Player Vita starting up!");
    StateMachine stateMachine = { .stateMachineCommand = STATE_MACHINE_COMMAND_INIT,
                                  .state = inGameRenderingState };

    while (stateMachine.stateMachineCommand != STATE_MACHINE_COMMAND_END_GAME) {
        vita2d_start_drawing();
        vita2d_clear_screen();
        updateStateMachine(&stateMachine);
        vita2d_end_drawing();
        vita2d_swap_buffers();
    }

    //sceKernelDelayThread(3*1000000);

    //writeToLogger("Info: TJA Player Vita shutting down...");
    cleanupStateMachine(&stateMachine);
    exitLogger();
    vita2d_fini();
    sceKernelExitProcess(0);
    return 0;
}