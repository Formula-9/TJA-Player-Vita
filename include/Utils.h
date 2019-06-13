#ifndef TJA_PLAYER_VITA_UTILS_H
#define TJA_PLAYER_VITA_UTILS_H

#include <dirent.h>

void findAllTjaFiles(const char *folderPath, int depthLevel);
const char *getLastFourCharactersOfString(const char *string);
int isTjaFile(struct dirent *dirEntry, const char *folderPath);
int isFolderAndNotParentOrCurrent(struct dirent *dirEntry, const char *folderPath);
int isFolder(struct dirent *dirEntry, const char *folderPath);
char *makePathFromDirAndString(const char *basePath, const char *extensionPath);
char *shiftJisToUtf8(char *shiftJisString);
size_t getStringSize(char *string);

#endif //TJA_PLAYER_VITA_UTILS_H
