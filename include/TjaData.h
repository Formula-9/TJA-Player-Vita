#ifndef TJA_PLAYER_VITA_TJADATA_H
#define TJA_PLAYER_VITA_TJADATA_H

#include <stdio.h>

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
void performFirstPass(TjaData *data, int level, FILE *fileDescriptor);
void logTjaData(TjaData *data);

#endif //TJA_PLAYER_VITA_TJADATA_H