#ifndef TJA_PLAYER_VITA_TJAFILE_H
#define TJA_PLAYER_VITA_TJAFILE_H

#include <string.h>
#include <stdlib.h>
#include <psp2/types.h>

#include "Utils.h"

typedef struct TjaFile {
    char *filePath;
    char *musicFile;
    int diff_easy;
    int diff_normal;
    int diff_hard;
    int diff_oni;
    int diff_edit;
} TjaFile;

TjaFile *makeTjaFileInstance(char *filePath);
void parseFileHeader(SceUID fileDescriptor, TjaFile *tjaFile);
void checkIfBufferEndsWithCourseAndReposition(SceUID fileDescriptor, char *buffer);
void repositionToClosestLineReturn(SceUID fileDescriptor, char *buffer);
void checkForLevelData(const char *buffer, TjaFile *file, const char *courseLevelHeader);
void checkForAnyLevelData(const char *buffer, TjaFile *file);
void checkForMusicFileName(const char *buffer, TjaFile *file);
void logTjaFile(TjaFile *tjaFile);
void freeTjaFile(TjaFile *file);

#endif //TJA_PLAYER_VITA_TJAFILE_H
