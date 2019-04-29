#ifndef TJA_PLAYER_VITA_LOGGER_H
#define TJA_PLAYER_VITA_LOGGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <psp2/io/fcntl.h>
#include <psp2/rtc.h>
#include <psp2/types.h>

/** SceIoOpen returns a SceUID, which is a typedef for int. See the VitaSDK docs. */
typedef SceUID Logger;

extern const char *DEFAULT_LOG_PATH;

void initializeLogger();
void writeToLogger(const char *message);
void exitLogger();

#endif //TJA_PLAYER_VITA_LOGGER_H
