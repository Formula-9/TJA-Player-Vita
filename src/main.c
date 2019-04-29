#include <psp2/kernel/processmgr.h>

#include "Logger.h"
//#include "StateMachine.h"
//#include "StateMachineCommand.h"
//#include "test/InGameRenderingState.h"
#include "Utils.h"

int main() {
    initializeLogger();


    exitLogger();
    sceKernelExitProcess(0);
    return 0;
}