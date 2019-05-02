#ifndef TJA_PLAYER_VITA_TJAFILE_H
#define TJA_PLAYER_VITA_TJAFILE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <psp2/io/fcntl.h>
#include <psp2/types.h>

#include "Logger.h"
#include "Constants.h"

typedef struct TjaFile {
    char *filePath;
    char *musicFile;
    char *title;
    char *subtitle;
    int diffEasy;
    int diffNormal;
    int diffHard;
    int diffOni;
    int diffEdit;
    int bpm;
    int musicVolume;
    int soundEffectVolume;
    int scoreMode;
    float offset;
    float demoStart;
} TjaFile;

TjaFile *makeTjaFileInstance(char *filePath);
void initBlankTjaFile(TjaFile *file);
void parseFileHeader(SceUID fileDescriptor, TjaFile *tjaFile);
void checkIfBufferEndsWithCourseAndReposition(SceUID fileDescriptor, char *buffer);
void repositionToClosestLineReturn(SceUID fileDescriptor, char *buffer);
void checkForMissingData(const char *buffer, TjaFile *tjaFile);
void checkForTitleData(const char *buffer, TjaFile *file);
void checkForSubtitleData(const char *buffer, TjaFile *file);
void checkForBpmData(const char *buffer, TjaFile *file);
void checkForMusicVolumeData(const char *buffer, TjaFile *file);
void checkForSoundEffectVolumeData(const char *buffer, TjaFile *file);
void checkForScoreModeData(const char *buffer, TjaFile *file);
void checkForOffsetData(const char *buffer, TjaFile *file);
void checkForDemoStartData(const char *buffer, TjaFile *file);
void checkForLevelData(const char *buffer, TjaFile *file, const char *courseLevelHeader);
void checkForAnyLevelData(const char *buffer, TjaFile *file);
void checkForMusicFileName(const char *buffer, TjaFile *file);
void logTjaFile(TjaFile *tjaFile);
void freeTjaFile(TjaFile *file);

#endif //TJA_PLAYER_VITA_TJAFILE_H
