#ifndef TJA_PLAYER_VITA_TJAFOLDER_H
#define TJA_PLAYER_VITA_TJAFOLDER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "TjaFile.h"
#include "Logger.h"

typedef struct TjaFolder {
    char     *folderName;
    TjaFile **files;
    int       currentCapacity;
    int       numberOfFiles;
} TjaFolder;

TjaFolder *newTjaFolder(const char *folderName, const int initialCapacity);
void addFileToFolder(TjaFolder *folder, TjaFile *file);
void sortTjaFolderByTitle(TjaFolder *folder);
void swapTjaFilePointers(TjaFile **file1, TjaFile **file2);
int tjaFolderTitlePartition(TjaFolder *folder, int low, int high);
void tjaFolderTitleQuickSort(TjaFolder *folder, int low, int high);
void freeTjaFolder(TjaFolder *folder);

#endif //TJA_PLAYER_VITA_TJAFOLDER_H
