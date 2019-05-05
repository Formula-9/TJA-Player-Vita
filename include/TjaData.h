#ifndef TJA_PLAYER_VITA_TJADATA_H
#define TJA_PLAYER_VITA_TJADATA_H

#include <stdio.h>

#include <psp2/io/fcntl.h>
#include <psp2/types.h>

#include "TjaFile.h"
#include "Logger.h"
#include "Constants.h"

typedef struct TjaData {
    TjaFile  *file;
    int      *notes;
    int       noteCount;
    int      *balloonHits;
    int       balloonCount;
    float    *bpmChange;
    int       bpmChangeCount;
    float    *scrollChange;
    int       scrollChangeCount;
} TjaData;

TjaData *makeTjaDataFromTjaFile(TjaFile *file, int level);
void initBlankTjaData(TjaData *data);
void performFirstPass(TjaData *data, int level, SceUID fileDescriptor);
void logTjaData(TjaData *data);

#endif //TJA_PLAYER_VITA_TJADATA_H