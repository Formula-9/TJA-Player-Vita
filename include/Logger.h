#ifndef TJA_PLAYER_VITA_LOGGER_H
#define TJA_PLAYER_VITA_LOGGER_H

#include <psp2/types.h>

#include "Constants.h"

/** SceIoOpen returns a SceUID, which is a typedef for int. See the VitaSDK docs. */
typedef SceUID Logger;

void initializeLogger();
void writeTimestamp();
void writeToLogger(const char *message);
void writeIntToLogger(int value);
void writePointerToLogger(void *ptr);
void exitLogger();

#endif //TJA_PLAYER_VITA_LOGGER_H
