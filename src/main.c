#include <psp2/kernel/processmgr.h>
#include <psp2/io/fcntl.h>

#include "../include/Logger.h"
//#include "StateMachine.h"
//#include "StateMachineCommand.h"
//#include "test/InGameRenderingState.h"
#include "../include/TjaFile.h"
#include "../include/Utils.h"

int main() {
    initializeLogger();
    findAllTjaFiles(DEFAULT_TJA_PATH, 0);
    exitLogger();
    sceKernelExitProcess(0);
    return 0;
}