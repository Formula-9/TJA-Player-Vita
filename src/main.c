#include <sys/time.h>
#include <psp2/kernel/processmgr.h>
#include <vita2d.h>

#include "../include/Logger.h"
#include "../include/StateMachine.h"
#include "../include/StateMachineCommand.h"
#include "../include/states/SongSelectState.h"
#include "../include/TjaFile.h"
#include "../include/Utils.h"
#include "../include/Constants.h"

int main() {
    vita2d_init();
    initializeLogger();

    findAllTjaFiles(DEFAULT_TJA_PATH, 0);

    /* StateMachine stateMachine = { .stateMachineCommand = STATE_MACHINE_COMMAND_INIT,
                                  .state = songSelectState };

    struct timeval frameStart, frameEnd;

    while (stateMachine.stateMachineCommand != STATE_MACHINE_COMMAND_END_GAME) {
        gettimeofday(&frameStart, NULL);
        vita2d_start_drawing();
        vita2d_clear_screen();
        updateStateMachine(&stateMachine);
        vita2d_end_drawing();
        vita2d_wait_rendering_done();
        vita2d_swap_buffers();
        gettimeofday(&frameEnd, NULL);
        sceKernelDelayThread(MAX_DELAY_MICROSECONDS - (frameEnd.tv_usec - frameStart.tv_usec));
    }

    //findAllTjaFiles(DEFAULT_TJA_PATH, 0);
    cleanupStateMachine(&stateMachine); */
    exitLogger();
    vita2d_fini();
    sceKernelExitProcess(0);
    return 0;
}