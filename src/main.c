#include <psp2/kernel/processmgr.h>

#include "Logger.h"
//#include "StateMachine.h"
//#include "StateMachineCommand.h"
//#include "test/InGameRenderingState.h"
#include "TjaFile.h"
#include "Utils.h"

int main() {
    initializeLogger();
    TjaFile *file = makeTjaFileInstance("ux0:/data/tjapvita/tja/Namco Original/Xa/Xa.tja");
    logTjaFile(file);
    file->filePath = NULL;
    freeTjaFile(file);
    exitLogger();
    sceKernelExitProcess(0);
    return 0;
}