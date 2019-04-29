#ifndef TJA_PLAYER_VITA_UTILS_H
#define TJA_PLAYER_VITA_UTILS_H

#include <psp2/types.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>

#include "Constants.h"
#include "Logger.h"

void logAllTjaFiles(const char *folderPath, int depth_level);
const char *getLastFourCharactersOfString(const char *string);
int isTjaFile(SceIoDirent dirEntry);
int isFolderAndNotParentOrCurrent(SceIoDirent dirEntry);
int isFolder(SceIoDirent dirEntry);
char *makePathFromDirAndString(const char *basePath, const char *extensionPath);

#endif //TJA_PLAYER_VITA_UTILS_H
