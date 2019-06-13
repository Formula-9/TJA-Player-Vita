#ifndef TJA_PLAYER_VITA_TJAFILE_H
#define TJA_PLAYER_VITA_TJAFILE_H

#include <stdio.h>

typedef struct TjaFile {
    char *filePath;
    char *musicFile;
    char *title;
    char *subtitle;
    int subtitleEffect;
    int diffEasy;
    int diffNormal;
    int diffHard;
    int diffOni;
    int diffEdit;
    float bpm;
    int musicVolume;
    int soundEffectVolume;
    int scoreMode;
    float offset;
    float demoStart;
} TjaFile;

TjaFile *makeTjaFileInstance(char *filePath);
void parseFileHeader(FILE *fileDescriptor, TjaFile *tjaFile);
void checkIfBufferEndsWithCourseAndReposition(FILE *fileDescriptor, char *buffer);
void repositionToClosestLineReturn(FILE *fileDescriptor, char *buffer);
void checkForMissingData(const char *buffer, TjaFile *tjaFile);
void checkForIntTypeData(const char *buffer, int *result, const char *header);
void checkForFloatTypeData(const char *buffer, float *result, const char *header);
void checkForStringTypeData(const char *buffer, char **result, const char *header);
void checkForLevelData(const char *buffer, TjaFile *file, const char *courseLevelHeader);
void checkForAnyLevelData(const char *buffer, TjaFile *file);
void logTjaFile(TjaFile *tjaFile);
void freeTjaFile(TjaFile *file);

#endif //TJA_PLAYER_VITA_TJAFILE_H
